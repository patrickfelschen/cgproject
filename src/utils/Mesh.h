//
// Created by Patrick on 05.08.2022.
//

#ifndef CG_MESH_H
#define CG_MESH_H


#include "Vertex.h"
#include "Texture.h"
#include "../shaders/Shader.h"
#include "Material.h"

class Mesh {
public:
    Mesh();

    Mesh(const std::vector<Vertex> &vertices,
         const std::vector<unsigned int> &indices,
         const std::vector<Texture> &textures,
         const Material &material);

    virtual ~Mesh();

    void render(Shader *shader) const;

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;
    Material material;
private:
    unsigned int VAO = 0;
    unsigned int VBO = 0;
    unsigned int EBO = 0;

    void setupMesh();
};


#endif //CG_MESH_H
