//
// Created by Patrick on 24.08.2022.
//

#include "ParticleModel.h"

ParticleModel::ParticleModel(ParticleShader *shader) : shader(shader) {
    std::vector<unsigned int> indices = {
            0, 1, 3, 3, 1, 2,
            1, 5, 2, 2, 5, 6,
            5, 4, 6, 6, 4, 7,
            4, 0, 7, 7, 0, 3,
            3, 2, 7, 7, 2, 6,
            4, 5, 0, 0, 5, 1
    };
    std::vector<Vertex> vertices = {
            Vertex(Vector3f(-1, -1, -1), Vector3f(), Vector2f(0, 0), Vector2f()),
            Vertex(Vector3f(1, -1, -1), Vector3f(), Vector2f(1, 0), Vector2f()),
            Vertex(Vector3f(1, 1, -1), Vector3f(), Vector2f(1, 1), Vector2f()),
            Vertex(Vector3f(-1, 1, -1), Vector3f(), Vector2f(0, 1), Vector2f()),
            Vertex(Vector3f(-1, -1, 1), Vector3f(), Vector2f(0, 0), Vector2f()),
            Vertex(Vector3f(1, -1, 1), Vector3f(), Vector2f(1, 0), Vector2f()),
            Vertex(Vector3f(1, 1, 1), Vector3f(), Vector2f(1, 1), Vector2f()),
            Vertex(Vector3f(-1, 1, 1), Vector3f(), Vector2f(0, 1), Vector2f()),
    };
    std::vector<Texture> textures = {
            Texture("../assets/Objects/Ghost/texture.png", "texture_defuse")
            //Texture()
    };
    Mesh particleMesh(vertices, indices, textures);
    this->meshes.push_back(particleMesh);
}

ParticleModel::~ParticleModel() = default;

void ParticleModel::render() const {
    this->shader->activate();
    for (auto &mesh: meshes) {
        mesh.render(shader);
    }
    this->shader->deactivate();
}

