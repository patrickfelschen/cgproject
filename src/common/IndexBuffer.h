//
// Created by Patrick on 04.08.2022.
//

#ifndef CG_INDEXBUFFER_H
#define CG_INDEXBUFFER_H


#include "GL/glew.h"

class IndexBuffer {
public:
    explicit IndexBuffer(const unsigned int *data, unsigned int count);

    virtual ~IndexBuffer();

    void bind() const;

    void unbind() const;

    unsigned int getCount() const;

private:
    GLuint id;
    unsigned int count;
};


#endif //CG_INDEXBUFFER_H
