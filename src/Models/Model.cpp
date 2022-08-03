//
// Created by Patrick on 01.08.2022.
//

#include "Model.h"
#include "../utils/Vertex.h"

Model::Model(const Shader &shader) : shader(shader) {
    Vertex vertices[] = {
            Vertex(Vector3f(0.5f, 0.5f, 0.5f), Vector2f(), Vector3f()),
            Vertex(Vector3f(-0.5f, 0.5f, -0.5f), Vector2f(), Vector3f()),
            Vertex(Vector3f(-0.5f, 0.5f, 0.5f), Vector2f(), Vector3f()),
            Vertex(Vector3f(0.5f, -0.5f, -0.5f), Vector2f(), Vector3f()),
            Vertex(Vector3f(-0.5f, -0.5f, -0.5f), Vector2f(), Vector3f()),
            Vertex(Vector3f(0.5f, 0.5f, -0.5f), Vector2f(), Vector3f()),
            Vertex(Vector3f(0.5f, -0.5f, 0.5f), Vector2f(), Vector3f()),
            Vertex(Vector3f(-0.5f, -0.5f, 0.5f), Vector2f(), Vector3f()),
    };

    // Handle zum Buffer erstellen
    glGenBuffers(1, &VBO);
    // Bufferobjekt binden
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // An GL_ARRAY_BUFFER gebundenes Objekt mit Vertexattribut-Daten füllen
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    unsigned int indices[] = {
            0, 1, 2,
            1, 3, 4,
            5, 6, 3,
            7, 3, 6,
            2, 4, 7,
            0, 7, 6,
            0, 5, 1,
            1, 5, 3,
            5, 0, 6,
            7, 4, 3,
            2, 1, 4,
            0, 2, 7
    };

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

void Model::update(float deltaTime) {
    Matrix scale = Matrix().identity();
    scale.scale(0.2f);

    Matrix rotation = Matrix().identity();
    rotation.rotationY(0.0f);

    Matrix translation = Matrix().identity();
    translation.translation(0.0f, 0.0f, 0.0f);

    Matrix worldTransformation = translation * rotation * scale;

    shader.setModelTransform(worldTransformation);
}

void Model::render(const Camera &camera) {
    shader.activate(camera);

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    // Position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, Vertex::pos));

    // TexCoords
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, Vertex::texCoords));

    // Normals
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, Vertex::normal));

    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);

    shader.deactivate();
}
