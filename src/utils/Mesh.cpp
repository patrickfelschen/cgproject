//
// Created by Patrick on 05.08.2022.
// https://learnopengl.com/code_viewer_gh.php?code=includes/learnopengl/mesh.h
//

#include "Mesh.h"


Mesh::Mesh() = default;

Mesh::Mesh(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &indices,
           const std::vector<Texture> &textures, const Material &material) {
    this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;
    this->material = material;
    this->hasMaterial = true;
    this->setupMesh();
}

Mesh::Mesh(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &indices,
           const std::vector<Texture> &textures) {
    this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;
    this->hasMaterial = false;
    this->setupMesh();
}

Mesh::~Mesh() = default;

void Mesh::setupMesh() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(
            GL_ARRAY_BUFFER,
            vertices.size() * sizeof(Vertex),
            &vertices[0],
            GL_STATIC_DRAW
    );

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(
            GL_ELEMENT_ARRAY_BUFFER,
            indices.size() * sizeof(unsigned int),
            &indices[0],
            GL_STATIC_DRAW
    );

    // vertex positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, pos));
    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, normal));
    // vertex texture coords0
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, texCoord0));
    // vertex texture coords1
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, texCoord1));

    glBindVertexArray(0);
}

void Mesh::render(Shader *shader) const {
    // Texturen aktivieren
    unsigned int diffCount = 0;
    unsigned int specCount = 0;
    unsigned int mixCount = 0;
    int unit = 0;
    for(auto& texture: textures){
        texture.activate(unit);
        if(texture.type == "texture_diffuse"){
            shader->setUniform(texture.type + std::to_string(diffCount++), unit++);
        }
        if(texture.type == "texture_specular"){
            shader->setUniform(texture.type + std::to_string(specCount++), unit++);
        }
        if(texture.type == "texture_mixmap"){
            shader->setUniform(texture.type + std::to_string(mixCount++), unit++);
        }
    }
    // Material Eigenschaften setzen
    if (hasMaterial) {
        shader->setUniform("uMaterial.ambient", material.ambient);
        shader->setUniform("uMaterial.diffuse", material.diffuse);
        shader->setUniform("uMaterial.specular", material.specular);
        shader->setUniform("uMaterial.shininess", material.shininess);
    }
    // Mesh zeichnen
    glBindVertexArray(VAO);
    glDrawElements(
            GL_TRIANGLES,
            indices.size(),
            GL_UNSIGNED_INT,
            nullptr
    );
    glBindVertexArray(0);
    // Texturen deaktivieren
    for(auto& texture: textures){
        texture.deactivate(unit--);
    }
    glActiveTexture(GL_TEXTURE0);
}




