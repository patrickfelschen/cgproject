#include "Texture.h"


Texture::Texture() : texId(0) {}

Texture::Texture(const char *filePath) {
    release();

    RGBImage texture(0, 0);
    Loader::readImageFile(filePath, texture);

    glGenTextures(1, &texId);
    glBindTexture(GL_TEXTURE_2D, texId);

    glTexStorage2D(
            GL_TEXTURE_2D,
            4, // num mipmaps
            GL_RGBA32F,
            texture.getWidth(),
            texture.getHeight()
    );
    glTexSubImage2D(
            GL_TEXTURE_2D,
            0,
            0,
            0,
            texture.getWidth(),
            texture.getHeight(),
            GL_RGBA,
            GL_FLOAT,
            texture.getData().data()
    );
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);
}

bool Texture::isValid() const {
    return texId > 0;
}

void Texture::release() {
    if (isValid()) {
        glDeleteTextures(1, &texId);
        texId = -1;
    }
}

void Texture::activate(int slot) {
    if (texId == 0 || slot < 0 || slot > 7)
        return;
    currentTextureUnit = slot;

    glActiveTexture(GL_TEXTURE0 + currentTextureUnit);
    glBindTexture(GL_TEXTURE_2D, texId);
}

void Texture::deactivate() {
    glBindTexture(GL_TEXTURE_2D, 0);
    if (currentTextureUnit > 0)
        glActiveTexture(GL_TEXTURE0 + currentTextureUnit - 1);
    currentTextureUnit = 0;
}
