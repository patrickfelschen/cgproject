//
//  Loader.cpp
//
//  Created by Patrick Felschen on 12.05.22.
//

#include "Loader.hpp"

RawModel Loader::loadToVAO(std::vector<float> positions, std::vector<float> textureCoords, std::vector<int> indices) {
    int vaoID = createVAO();
    bindIndicesBuffer(indices);
    storeDataInAttributeList(0, 3, positions);
    storeDataInAttributeList(1, 2, textureCoords);
    unbindVAO();
    return RawModel(vaoID, indices.size());
}

void Loader::cleanUp() {
    for (GLuint vao: vaos) {
        glDeleteVertexArrays(1, &vao);
    }

    for (GLuint vbo: vbos) {
        glDeleteBuffers(1, &vbo);
    }

    for (GLuint texture: textures) {
        glDeleteTextures(1, &texture);
    }
}

GLuint Loader::loadTexture(std::string filepath) {
    GLuint texID;
    bool textureLoaded = TextureLoader::Inst()->getTexture(filepath, &texID);

    if (!textureLoaded) {
        std::cerr << "Texture " << filepath << " konnte nicht geladen werden." << std::endl;
        exit(EXIT_FAILURE);
    }

    textures.push_back(texID);

    return texID;
}

int Loader::createVAO() {
    GLuint vaoID;
    glGenVertexArrays(1, &vaoID);
    vaos.push_back(vaoID);
    glBindVertexArray(vaoID);

    return vaoID;
}

void Loader::storeDataInAttributeList(GLuint attributeNumber, unsigned int coordinateSize, std::vector<float> data) {
    GLuint vboID;
    glGenBuffers(1, &vboID);
    vbos.push_back(vboID);
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(attributeNumber, coordinateSize, GL_FLOAT, false, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Loader::bindIndicesBuffer(std::vector<int> indices) {
    GLuint vboID;
    glGenBuffers(1, &vboID);
    vbos.push_back(vboID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int), indices.data(), GL_STATIC_DRAW);
}


void Loader::unbindVAO() {
    glBindVertexArray(0);
}

Loader::Loader() {
}

Loader::~Loader() {
}


