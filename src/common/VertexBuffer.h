//
// Created by Patrick on 04.08.2022.
//

#ifndef CG_VERTEXBUFFER_H
#define CG_VERTEXBUFFER_H


#include "GL/glew.h"

class VertexBuffer {
public:
    explicit VertexBuffer(const void *data, unsigned int size);

    virtual ~VertexBuffer();

    void bind() const;

    void unbind() const;

private:
    GLuint id;
};


#endif //CG_VERTEXBUFFER_H
