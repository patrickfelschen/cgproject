//
// Quelle: https://learnopengl.com/Model-Loading/Mesh
//

#include "Mesh.h"

Mesh::Mesh() {
}

Mesh::Mesh(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &indices,
           const std::vector<Texture> &textures) {
    this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;
}

Mesh::~Mesh() {
}