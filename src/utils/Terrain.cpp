//
// Created by Patrick on 12.08.2022.
// https://www.braynzarsoft.net/viewtutorial/q16390-30-heightmap-terrain
//

#include "Terrain.h"
#include "Vertex.h"

Terrain::Terrain(Shader *shader) : Model(shader), width(10), height(1), depth(10) {
    generate();
}

void Terrain::generate() {
    RGBImage image;
    Loader::readImageFile("../assets/Terrain/heightmap.bmp", image);

    unsigned int imgWidth = image.getWidth();
    unsigned int imgHeight = image.getHeight();

    float widthScale = width / imgWidth;
    float heightScale = depth / imgHeight;

    unsigned int vertexCount = imgWidth * imgHeight;

    std::vector<Vertex> vertices = std::vector<Vertex>(vertexCount);
    std::vector<unsigned int> indices = std::vector<unsigned int>(6 * (imgWidth - 1) * (imgHeight - 1));
    std::vector<Texture> textures = std::vector<Texture>();

    for (unsigned int i = 0; i < imgWidth; i++) {
        for (unsigned int j = 0; j < imgHeight; j++) {
            unsigned int index = i * imgWidth + j;
            float x = (j * heightScale - (depth / 2));
            float y = image.getPixelColor(i, j).r * this->height;
            float z = (i * widthScale - (width / 2));

            vertices[index].pos = Vector3f(x, y, z);
            // Texturkoordinaten für Grastextur
            vertices[index].texCoord0.x = (i / (float) imgWidth - 1);
            vertices[index].texCoord0.y = (j / (float) imgHeight - 1);
            // Texturkoordinaten für Steintextur
            vertices[index].texCoord1.x = (i / ((float) imgWidth - 1) * 100);
            vertices[index].texCoord1.y = (j / ((float) imgHeight - 1) * 100);
        }
    }
    int pos = 0;
    for (unsigned int i = 0; i < imgWidth - 1; i++) {
        int topLeft = 0;
        int topRight = 0;
        int bottomLeft = 0;
        int bottomRight = 0;
        // Eckpunkt f�r ein Viereck, 6 Punkte, da 2 Dreiecke
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
    for (unsigned int i = 0; i < indices.size(); i += 3) {
        Vector3f p0 = vertices[indices[i + 0]].pos;
        Vector3f p1 = vertices[indices[i + 1]].pos;
        Vector3f p2 = vertices[indices[i + 2]].pos;
        Vector3f e1 = p1 - p0;
        Vector3f e2 = p2 - p0;
        Vector3f normal = e1.cross(e2);
        normal = normal.normalize();
        vertices[indices[i + 0]].normal += normal;
        vertices[indices[i + 1]].normal += normal;
        vertices[indices[i + 2]].normal += normal;
    }

    // Texturen
    Texture grassTexture = Texture("../assets/Terrain/grass.bmp", "");
    Texture rockTexture = Texture("../assets/Terrain/rock.bmp", "");
    Texture mixTexture = Texture("../assets/Terrain/mixmap.bmp", "");

    textures.push_back(grassTexture);
    textures.push_back(rockTexture);
    textures.push_back(mixTexture);

    Mesh terrainMash = Mesh(vertices, indices, textures);

    this->meshes.push_back(terrainMash);
}

void Terrain::update(float deltaTime) {
    Model::update(deltaTime);
}

void Terrain::render(const Camera &camera) {
    this->shader->activate(camera);
    Model::render(camera);
    for (auto &mesh: meshes) {
        mesh.render();
    }
    this->shader->deactivate();
}
