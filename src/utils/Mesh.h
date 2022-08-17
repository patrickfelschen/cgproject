//
// Created by Patrick on 05.08.2022.
//

#ifndef CG_MESH_H
#define CG_MESH_H


#include "Vertex.h"
#include "Texture.h"
#include "../shaders/Shader.h"

class Mesh {
public:
    Mesh();

    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);

    virtual ~Mesh();

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    void render();

    unsigned int materialIndex;
private:
    unsigned int VAO, VBO, EBO;

    void setupMesh();
};


#endif //CG_MESH_H
