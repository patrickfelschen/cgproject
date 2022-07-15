//
//  Loader.cpp
//
//  Created by Patrick Felschen on 12.05.22.
//

#include "Loader.hpp"


RawModel Loader::loadToVAO(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &indices) {
    int vaoID = createVAO();
    bindIndicesBuffer(indices);
    storeVerticesInAttributeList(vertices);
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

GLuint Loader::loadTexture(const std::string &filepath) {
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

void Loader::storeVerticesInAttributeList(const std::vector<Vertex> &vertices) {
    GLuint vboID;
    glGenBuffers(1, &vboID);
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) nullptr);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, normal));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, texCoords));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Loader::bindIndicesBuffer(const std::vector<unsigned int> &indices) {
    GLuint vboID;
    glGenBuffers(1, &vboID);
    vbos.push_back(vboID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
}

void Loader::unbindVAO() {
    glBindVertexArray(0);
}

Loader::Loader() {
}

Loader::~Loader() {
}


