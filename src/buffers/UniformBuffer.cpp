//
// Created by Patrick on 30.08.2022.
//

#include <iostream>
#include "UniformBuffer.h"

UniformBuffer::UniformBuffer(unsigned int size, unsigned int binding) {
    glGenBuffers(1, &id);
    glBindBuffer(GL_UNIFORM_BUFFER, id);
    glBufferData(GL_UNIFORM_BUFFER, size, nullptr, GL_STATIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    glBindBufferBase(GL_UNIFORM_BUFFER, binding, id);
}

UniformBuffer::~UniformBuffer() {
    glDeleteBuffers(1, &id);
}

void UniformBuffer::setSubData(GLintptr offset, GLsizeiptr size, const void *data) {
    glBindBuffer(GL_UNIFORM_BUFFER, id);
    glBufferSubData(GL_UNIFORM_BUFFER, offset, size, data);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}
