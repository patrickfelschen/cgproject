#ifndef CG_TEXTURE_H
#define CG_TEXTURE_H


#include "GL/glew.h"
#include "FreeImage.h"
#include "../utils/RGBImage.h"
#include "../utils/Color.h"
#include <iostream>
#include <assert.h>

class Texture {
private:
    GLuint texId;
    RGBImage *pImage = nullptr;
    int currentTextureUnit;

    bool isValid() const;

    bool load(const char *filename);

    void release();

protected:
    RGBImage *createImage(unsigned char *data, unsigned int width, unsigned int height);

public:
    Texture();

    Texture(const char *filename);

    void activate(int slot);

    void deactivate();
};


#endif //CG_TEXTURE_H
