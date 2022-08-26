//
// Created by Patrick on 17.08.2022.
//

#include "Texture.h"

Texture::Texture() {}

Texture::Texture(const std::string& type) : id(0), type(type) {
    // Weiße Textur für texturlose Objekte
    RGBImage image(1, 1, GL_RGBA);
    image.setPixelColor(0, 0, Color(1.0f));
    create(image);
}

Texture::Texture(const Color &pixel, const std::string& type) {
    RGBImage image(1, 1, GL_RGBA);
    image.setPixelColor(0, 0, pixel);
    create(image);
}

Texture::Texture(const std::string &filePath, const std::string &type) : id(0), filePath(filePath), type(type) {
    RGBImage image;
    Loader::getInstance().readImageFile(filePath.c_str(), image);
    create(image);
}

Texture::~Texture() {
    //glDeleteTextures(1, &id);
}

void Texture::create(RGBImage &image) {
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);

    glTexStorage2D(
            GL_TEXTURE_2D,
            1, // num mipmaps
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

void Texture::deactivate(unsigned int unit) const {
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, 0);
}
