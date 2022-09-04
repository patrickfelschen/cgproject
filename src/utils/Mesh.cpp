//
// Created by Patrick on 05.08.2022.
// https://learnopengl.com/Model-Loading/Mesh
// https://learnopengl.com/code_viewer_gh.php?code=includes/learnopengl/mesh.h
//

#include "Mesh.h"


Mesh::Mesh() = default;

/**
 * Erzeugt ein gebündeltes Mesh Objekt
 * @param vertices Vertex Liste
 * @param indices Index Liste
 * @param textures Texturen Liste
 * @param material Materialeigenschaft
 */
Mesh::Mesh(const std::vector<Vertex> &vertices,
           const std::vector<unsigned int> &indices,
           const std::vector<Texture> &textures,
           const Material &material) {
    this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;
    this->material = material;
    this->hasMaterial = true;
    this->setupMesh();
}

/**
 * Erzeugt ein gebündeltes Mesh Objekt ohne Materialeigenschaft
 * @param vertices Vertex Liste
 * @param indices Index Liste
 * @param textures Texturen Liste
 */
Mesh::Mesh(const std::vector<Vertex> &vertices,
           const std::vector<unsigned int> &indices,
           const std::vector<Texture> &textures) {
    this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;
    this->hasMaterial = false;
    this->setupMesh();
}

Mesh::~Mesh() = default;

/**
 * Erzeugt notwendeige Buffer und lädt alle nötigen Vertex-Attribute
 */
void Mesh::setupMesh() {
    // Erzeugt ein Vertex Array Objekt (VAO)
    glGenVertexArrays(1, &VAO);
    // Erzeugt ein Vertex Buffer Objekt (VBO)
    glGenBuffers(1, &VBO);
    // Erzeugt ein Elements Buffer Objekt (EBO)
    glGenBuffers(1, &EBO);

    // Erzeugt das VAO und aktiviert es
    glBindVertexArray(VAO);

    // Erzeugt das VBO und aktiviert es
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // Lädt alle Vertices ins VBO
    // https://learnopengl.com/Getting-started/Hello-Triangle (Vertex input)
    glBufferData(
            GL_ARRAY_BUFFER,
            static_cast<GLsizeiptr>(vertices.size() * sizeof(Vertex)),
            &vertices[0],
            GL_STATIC_DRAW
    );

    // Erzeugt das EBO und aktiviert es
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // Lädt alle Indices ins EBO
    // https://learnopengl.com/Getting-started/Hello-Triangle (Element Buffer Objects)
    glBufferData(
            GL_ELEMENT_ARRAY_BUFFER,
            static_cast<GLsizeiptr>(indices.size() * sizeof(unsigned int)),
            &indices[0],
            GL_STATIC_DRAW
    );

    // Vertex Array Objekt
    // https://learnopengl.com/Getting-started/Hello-Triangle (Linking Vertex Attributes)
    // Positionen der Vertices (location 0)
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, pos));
    // Normalen der Vertices (location 1)
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, normal));
    // Textur Koordinaten der Vertices (location 2)
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, texCoord0));
    // Textur Koordinaten der Vertices (location 3)
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, texCoord1));
    // Deaktivieren
    glBindVertexArray(0);
}

/**
 * Zeichnet aktuelles Mesh und setzt im übergebenen (aktivierten) Shader
 * Texturen und Materialeigenschaften
 * @param shader aktivierter Shader
 */
void Mesh::render(Shader *shader) const {
    // Texturen aktivieren
    unsigned int diffCount = 0;
    unsigned int specCount = 0;
    unsigned int mixCount = 0;
    int unit = 0;
    for (auto &texture: textures) {
        texture.activate(unit);
        if (texture.type == "texture_diffuse") {
            shader->setUniform(texture.type + std::to_string(diffCount++), unit++);
        }
        if (texture.type == "texture_specular") {
            shader->setUniform(texture.type + std::to_string(specCount++), unit++);
        }
        if (texture.type == "texture_mixmap") {
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
            (GLsizei) indices.size(),
            GL_UNSIGNED_INT,
            nullptr
    );
    glBindVertexArray(0);
    // Texturen deaktivieren
    for (auto &texture: textures) {
        texture.deactivate(unit--);
    }
    // Standard Unit setzen
    glActiveTexture(GL_TEXTURE0);
}




