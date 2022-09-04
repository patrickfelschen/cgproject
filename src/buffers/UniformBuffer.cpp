//
// Created by Patrick on 30.08.2022.
// https://learnopengl.com/Advanced-OpenGL/Advanced-GLSL (Uniform buffer objects)
//

#include <iostream>
#include "UniformBuffer.h"

/**
 * Erstellt und initialisiert einen Uniform Buffer
 * @param size Größe in Bytes, des Buffers
 * @param binding Index an welchem der Buffer gebunden werden soll
 */
UniformBuffer::UniformBuffer(unsigned int size, unsigned int binding) {
    // Uniform Buffer erstellen
    glGenBuffers(1, &id);
    glBindBuffer(GL_UNIFORM_BUFFER, id);
    // Buffer initialisieren mit einer Größe von size Bytes
    glBufferData(GL_UNIFORM_BUFFER, (GLsizeiptr) size, nullptr, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    // Buffer an binding index binden
    glBindBufferBase(GL_UNIFORM_BUFFER, binding, id);
}

/**
 * Uniform Buffer entfernen
 */
UniformBuffer::~UniformBuffer() {
    glDeleteBuffers(1, &id);
}

/**
 * Setzt in Uniform Buffer Bereich neue Daten
 * @param offset Buffer Index, ab wann Daten verändert werden sollen
 * @param size Anzahl an Bytes, welche ab dem offset verändert werden sollen
 * @param data Dantenbytes
 */
void UniformBuffer::setSubData(int offset, unsigned int size, const void *data) const {
    glBindBuffer(GL_UNIFORM_BUFFER, id);
    glBufferSubData(GL_UNIFORM_BUFFER, offset, (GLsizeiptr) size, data);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}
