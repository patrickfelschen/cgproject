
#include "Texture.h"

Texture::Texture() : texId(0) {}

Texture::Texture(const char *filename) {
    bool result = load(filename);
    if (!result) {
        std::cerr << "ERROR::TEXTURE: can not load texture" << std::endl;
        exit(EXIT_FAILURE);
    }
}

bool Texture::isValid() const {
    return texId > 0;
}

bool Texture::load(const char *filename) {
    release();
    FREE_IMAGE_FORMAT imageFormat = FreeImage_GetFileType(filename, 0);
    if (imageFormat == FIF_UNKNOWN)
        imageFormat = FreeImage_GetFIFFromFilename(filename);

    if (imageFormat == FIF_UNKNOWN) {
        std::cerr << "WARNING::TEXTURE: unkown texture format" << std::endl;
        return false;
    }

    FIBITMAP *pBitmap = FreeImage_Load(imageFormat, filename);
    if (pBitmap == NULL) {
        std::cerr << "ERROR::TEXTURE: unable to open texture: " << filename << std::endl;
        exit(EXIT_FAILURE);
    }

    FREE_IMAGE_TYPE type = FreeImage_GetImageType(pBitmap);
    assert(type == FIT_BITMAP);

    unsigned int width = FreeImage_GetWidth(pBitmap);
    unsigned int height = FreeImage_GetHeight(pBitmap);
    unsigned int bpp = FreeImage_GetBPP(pBitmap);
    assert(bpp == 32 || bpp == 16 || bpp == 24);

    unsigned char *data = new unsigned char[width * height * 4];
    unsigned char *pData = (data - 1);

    if (data == NULL) {
        FreeImage_Unload(pBitmap);
        return false;
    }

    RGBQUAD color;
    for (unsigned int i = 0; i < height; ++i) {
        for (unsigned int j = 0; j < width; ++j) {
            FreeImage_GetPixelColor(pBitmap, j, height - i - 1, &color);
            *(++pData) = color.rgbRed;
            *(++pData) = color.rgbGreen;
            *(++pData) = color.rgbBlue;
            if (bpp == 32)
                *(++pData) = color.rgbReserved;
            else
                *(++pData) = 255;
        }
    }

    FreeImage_Unload(pBitmap);

    if (pImage)
        delete pImage;

    pImage = createImage(data, width, height);

    glGenTextures(1, &texId);

    glBindTexture(GL_TEXTURE_2D, texId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glBindTexture(GL_TEXTURE_2D, 0);

    delete[] data;
    return true;
}

void Texture::release() {
    if (isValid()) {
        glDeleteTextures(1, &texId);
        texId = -1;
    }
    if (pImage)
        delete pImage;
    pImage = NULL;
}

RGBImage *Texture::createImage(unsigned char *data, unsigned int width, unsigned int height) {
    RGBImage *img = new RGBImage(width, height);
    assert(img);
    for (unsigned int i = 0; i < height; i++) {
        for (unsigned int j = 0; j < width; j++) {
            Color c((float) *(data) / 255.0f, (float) *(data + 1) / 255.0f, (float) *(data + 2) / 255.0f);
            img->setPixelColor(j, i, c);
            data += 4;
        }
    }
    return img;
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



