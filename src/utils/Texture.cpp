//
// Created by Patrick on 17.08.2022.
//



#include "Texture.h"

Texture::Texture() : id(0), filePath(""), type("") {}

Texture::~Texture() {
    //glDeleteTextures(1, &id);
}

Texture::Texture(const std::string &filePath, const std::string &type) : id(0), filePath(filePath), type(type) {
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);

    RGBImage image;
    Loader::readImageFile(filePath.c_str(), image);

    glTexStorage2D(
            GL_TEXTURE_2D,
            4, // num mipmaps
            GL_RGBA32F,
            image.getWidth(),
            image.getHeight()
    );

    glTexSubImage2D(
            GL_TEXTURE_2D,
            0,
            0,
            0,
            image.getWidth(),
            image.getHeight(),
            GL_RGBA,
            GL_FLOAT,
            image.getData().data()
    );
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
}

void Texture::activate(unsigned int unit) const {
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, id);
}

void Texture::deactivate() const {
    glBindTexture(GL_TEXTURE_2D, 0);
}




