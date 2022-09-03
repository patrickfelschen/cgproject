//
// Created by Patrick on 12.08.2022.
// https://www.braynzarsoft.net/viewtutorial/q16390-30-heightmap-terrain
//

#include "TerrainModel.h"

TerrainModel::TerrainModel(TerrainShader *shader) : Model() {
    this->shader = shader;
    this->size = 200;
    this->height = 6.5;
    this->width = size;
    this->depth = size;
    this->generate();
}

/**
 * Erstellt eine Landschaft auf Basis einer HeightMap
 */
void TerrainModel::generate() {
    // HeightMap Bild einlesen
    RGBImage image;
    Loader::getInstance().readImageFile("../assets/Terrain/heightmap.bmp", image);

    // Auslesen der Breite und Höhe der Heightmap
    this->imgWidth = image.getWidth();
    this->imgHeight = image.getHeight();

    // Nur quadratisches Format zulassen
    assert(imgWidth == imgHeight);

    // Weiten- und Höhenskalierung berechnung
    // widthScale/heightScale ermöglichen Skalierung der Werte über size
    float widthScale = width / imgWidth;
    float heightScale = depth / imgHeight;

    // Anzahl der Vertices anhand der HeightMap Weite und Höhe berechnen
    unsigned int vertexCount = imgWidth * imgHeight;

    // Speicher für Terrain Höhen um Kollisionen zu erkennen
    heights.resize(vertexCount);

    // Speicher initialisieren
    std::vector<Vertex> vertices = std::vector<Vertex>(vertexCount);
    std::vector<unsigned int> indices = std::vector<unsigned int>(6 * (imgWidth - 1) * (imgHeight - 1));
    std::vector<Texture> textures = std::vector<Texture>();

    // Alle Bild Farben iterieren und Vertices erstellen
    for (unsigned int i = 0; i < imgWidth; i++) {
        for (unsigned int j = 0; j < imgHeight; j++) {
            unsigned int index = i * imgWidth + j;

            // Vertex Position skalieren und
            // verschieben, sodass Nullpunkt mitte vom Terrain ist
            float x = (j * heightScale - (depth / 2));
            float z = (i * widthScale - (width / 2));
            // Vertex Höhe anhand der Bild Farbe ermitteln
            float y = image.getPixelColor(i, j).r * this->height;

            // Höhe für Kollisionen setzen
            heights[j * imgWidth + i] = y;

            // Vertex Position setzen
            vertices[index].pos = Vector3f(x, y, z);

            // Texturkoordinaten für Mixtextur setzen
            vertices[index].texCoord0.x = (i / (float) imgWidth - 1);
            vertices[index].texCoord0.y = (j / (float) imgHeight - 1);
            // Texturkoordinaten für Grastextur und Steintextur setzen
            vertices[index].texCoord1.x = (i / ((float) imgWidth - 1) * size);
            vertices[index].texCoord1.y = (j / ((float) imgHeight - 1) * size);
        }
    }
    int pos = 0;
    // Alle Bild Farben erneut iterieren und Indices erstellen
    for (unsigned int i = 0; i < imgWidth - 1; i++) {
        int topLeft = 0;
        int topRight = 0;
        int bottomLeft = 0;
        int bottomRight = 0;
        // Eckpunkt für ein Viereck, 6 Punkte, da 2 Dreiecke
        for (int j = 0; j < imgHeight - 1; j++) {
            topLeft = (i * imgWidth) + j;
            topRight = topLeft + 1;
            bottomLeft = ((i + 1) * imgWidth) + j;
            bottomRight = bottomLeft + 1;
            // Dreieck 1
            indices[pos++] = topLeft;
            indices[pos++] = bottomLeft;
            indices[pos++] = topRight;
            // Dreieck 2
            indices[pos++] = topRight;
            indices[pos++] = bottomLeft;
            indices[pos++] = bottomRight;
        }
    }
    // Gemittelte Normalen pro Dreieck erstellen
    // https://gamedev.stackexchange.com/a/66937
    for (unsigned int i = 0; i < indices.size(); i += 3) {
        // Drei Vertices eines Faces holen
        Vector3f p0 = vertices[indices[i + 0]].pos;
        Vector3f p1 = vertices[indices[i + 1]].pos;
        Vector3f p2 = vertices[indices[i + 2]].pos;
        // Ebene aufstellen
        Vector3f e1 = p1 - p0;
        Vector3f e2 = p2 - p0;
        // Senkrechte über Kreuzprodukt berechnen
        Vector3f normal = e1.cross(e2);
        // Normalisieren
        normal = normal.normalize();
        // Summieren (Summe jetzt nicht mehr normalisiert!)
        vertices[indices[i + 0]].normal += normal;
        vertices[indices[i + 1]].normal += normal;
        vertices[indices[i + 2]].normal += normal;
    }

    // Alle summierten Normalen normalisieren
    for (auto &vertex: vertices) {
        vertex.normal.normalize();
    }

    // Texturen erstellen
    Texture grassTexture = Texture("../assets/Terrain/grass.bmp", "texture_diffuse");
    Texture rockTexture = Texture("../assets/Terrain/rock.bmp", "texture_diffuse");
    Texture mixTexture = Texture("../assets/Terrain/mixmap.bmp", "texture_mixmap");
    Texture specTexture = Texture("texture_specular"); // Weiß

    // Texturen hinzufügen
    textures.push_back(grassTexture);
    textures.push_back(rockTexture);
    textures.push_back(mixTexture);
    textures.push_back(specTexture);

    // Mesh erstellen
    Mesh terrainMash = Mesh(vertices, indices, textures, Material());
    this->meshes.push_back(terrainMash);
}

void TerrainModel::render() const {
    this->shader->activate();
    for (auto &mesh: meshes) {
        mesh.render(shader);
    }
    this->shader->deactivate();
}

/**
 * Berechnet die Höhe (y-Koordinate) auf dem Terrain
 * Quelle: https://www.youtube.com/watch?v=6E2zjfzMs7c
 * @param worldX x-Position auf Terrain
 * @param worldZ z-Position auf Terrain
 * @param onTerrain liefer zurück ob sich Position auf Terrain befinden
 * @return height der Angegebenen Position
 */
float TerrainModel::getHeightOfTerrain(float worldX, float worldZ, bool &onTerrain) const {
    // Welt-Position auf dem Terrain (Start in Mittelpunkt)
    float terrainX = worldX + width / 2;
    float terrainZ = worldZ + depth / 2;
    //std::cout << "X: " << terrainX << std::endl;
    //std::cout << "Z " << terrainZ << std::endl;

    // Größe eines Quadrats des Terrains
    float gridSquareSize = size / (float) (imgWidth - 1);
    //std::cout << gridSquareSize << std::endl;

    // Koordinaten des aktuellen Quadrats
    float gridX = std::floor(terrainX / gridSquareSize);
    float gridZ = std::floor(terrainZ / gridSquareSize);
    //std::cout << "X: " << gridX << std::endl;
    //std::cout << "Z " << gridZ << std::endl;

    if ((int) gridX >= imgWidth - 1 ||
        (int) gridZ >= imgWidth - 1 ||
        (int) gridX < -(int) (imgWidth - 1) ||
        (int) gridX < -(int) (imgWidth - 1)) {
        std::cout << "TERRAIN::GET_HEIGHT: OUT OF BOUNDS" << std::endl;
        onTerrain = false;
        return 0;
    }

    // Position im Quadrat
    float xCoord = fmod(terrainX, gridSquareSize) / gridSquareSize;
    float zCoord = fmod(terrainZ, gridSquareSize) / gridSquareSize;
    //std::cout << xCoord << std::endl;
    //std::cout << zCoord << std::endl;

    // 1 - zCoord = Diagonale des Quadrats, Prüfung in welcher Hälfte (Quadrat bestehend aus 2 Dreiecken)
    // man sich befindet, danach Lage des Punktes im Dreieck bestimmen
    float terrainHeight = 0;
    if (xCoord <= (1 - zCoord)) {
        terrainHeight = baryCentric(
                Vector3f(0, heights[(gridX * imgWidth) + gridZ], 0),
                Vector3f(1, heights[((gridX + 1) * imgWidth) + gridZ], 0),
                Vector3f(0, heights[(gridX * imgWidth) + (gridZ + 1)], 1),
                Vector2f(xCoord, zCoord)
        );
    } else {
        terrainHeight = baryCentric(
                Vector3f(1, heights[((gridX + 1) * imgWidth) + gridZ], 0),
                Vector3f(1, heights[((gridX + 1) * imgWidth) + (gridZ + 1)], 1),
                Vector3f(0, heights[(gridX * imgWidth) + (gridZ + 1)], 1),
                Vector2f(xCoord, zCoord)
        );
    }
    onTerrain = true;
    return terrainHeight;
}

// https://de.wikipedia.org/wiki/Baryzentrische_Koordinaten#:~:text=tfrac%20%7B1%7D%7B2%7D%7D)%5C%3B.%7D-,In%20einer%20Ebene%20(n%3D3%2C%20Dreieck),-%5BBearbeiten%20%7C
float TerrainModel::baryCentric(Vector3f p1, Vector3f p2, Vector3f p3, Vector2f pos) const {
    float det = (p2.z - p3.z) * (p1.x - p3.x) + (p3.x - p2.x) * (p1.z - p3.z);
    float l1 = ((p2.z - p3.z) * (pos.x - p3.x) + (p3.x - p2.x) * (pos.y - p3.z)) / det;
    float l2 = ((p3.z - p1.z) * (pos.x - p3.x) + (p1.x - p3.x) * (pos.y - p3.z)) / det;
    float l3 = 1.0f - l1 - l2;
    return l1 * p1.y + l2 * p2.y + l3 * p3.y;
}

float TerrainModel::getSize() const {
    return size;
}
