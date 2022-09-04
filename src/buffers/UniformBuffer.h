//
// Created by Patrick on 30.08.2022.
//

#ifndef CG_UNIFORMBUFFER_H
#define CG_UNIFORMBUFFER_H


#include "GL/glew.h"

class UniformBuffer {
public:
    UniformBuffer(unsigned int size, unsigned int binding);

    virtual ~UniformBuffer();

    void setSubData(int offset, unsigned int size, const void *data) const;

private:
    GLuint id = 0;
};


#endif //CG_UNIFORMBUFFER_H
