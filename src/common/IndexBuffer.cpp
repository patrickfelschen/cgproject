//
// Created by Patrick on 04.08.2022.
//

#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(const unsigned int *data, unsigned int count) : id(-1), count(count) {
    glGenBuffers(1, &id);
    glBindBuffer(GL_ARRAY_BUFFER, id);
    glBufferData(GL_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer() {
    glDeleteBuffers(1, &id);
}

void IndexBuffer::bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, id);
}

void IndexBuffer::unbind() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

unsigned int IndexBuffer::getCount() const {
    return count;
}
