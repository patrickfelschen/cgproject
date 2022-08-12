#ifndef CG_TEXTURE_H
#define CG_TEXTURE_H


#include "GL/glew.h"
#include "FreeImage.h"
#include "../utils/RGBImage.h"
#include "../utils/Color.h"
#include <iostream>
#include <cassert>
#include "../utils/Loader.h"

class Texture {
public:
    Texture();

    Texture(const char *filePath);

    void activate(int slot);

    void deactivate();

private:
    GLuint texId;
    int currentTextureUnit;

    bool isValid() const;

    void release();
};


#endif //CG_TEXTURE_H
