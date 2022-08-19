//
// Created by Patrick on 12.08.2022.
// https://www.braynzarsoft.net/viewtutorial/q16390-30-heightmap-terrain
//

#include "TerrainModel.h"
#include "../utils/Vertex.h"

TerrainModel::TerrainModel(Shader *shader) : Model(shader), width(1000), height(0.5), depth(1000) {
    generate();
}

void TerrainModel::generate() {
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
            // Texturkoordinaten für Mixtextur
            vertices[index].texCoord0.x = (i / (float) imgWidth - 1);
            vertices[index].texCoord0.y = (j / (float) imgHeight - 1);
            // Texturkoordinaten für Grastextur und Steintextur
            vertices[index].texCoord1.x = (i / ((float) imgWidth - 1) * 200);
            vertices[index].texCoord1.y = (j / ((float) imgHeight - 1) * 200);
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

    Material material;
    Mesh terrainMash = Mesh(vertices, indices, textures, material);

    this->meshes.push_back(terrainMash);
}

void TerrainModel::update(float deltaTime) const {
    Model::update(deltaTime);
}

void TerrainModel::render(const Camera &camera, const Matrix &transform) const {
    this->shader->activate(camera);
    Model::render(camera, transform);
    for (auto &mesh: meshes) {
        mesh.render(shader);
    }
    this->shader->deactivate();
}
