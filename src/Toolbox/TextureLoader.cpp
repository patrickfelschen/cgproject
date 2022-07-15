//
//  TextureLoader.cpp
//  CGXcode
//
//  Created by Patrick Felschen on 02.06.22.
//  Quelle: https://github.com/WinMerge/freeimage/blob/master/Examples/OpenGL/TextureManager/TextureManager.cpp
//

#include "TextureLoader.hpp"

TextureLoader *TextureLoader::m_inst(nullptr);

TextureLoader *TextureLoader::Inst() {
    if (!m_inst)
        m_inst = new TextureLoader();

    return m_inst;
}

TextureLoader::TextureLoader() {
    // call this ONLY when linking with FreeImage as a static library
#ifdef FREEIMAGE_LIB
    FreeImage_Initialise();
#endif
}

TextureLoader::~TextureLoader() {
    // call this ONLY when linking with FreeImage as a static library
#ifdef FREEIMAGE_LIB
    FreeImage_DeInitialise();
#endif

    m_inst = nullptr;
}

bool
TextureLoader::getTexture(std::string filepath, GLuint *texID, GLenum image_format, GLint internal_format, GLint level,
                          GLint border) {
    //image format
    FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
    //pointer to the image, once loaded
    FIBITMAP *dib(0);
    //pointer to the image data
    BYTE *bits(0);
    //image width and height
    unsigned int width(0), height(0);

    //check the file signature and deduce its format
    fif = FreeImage_GetFileType(filepath.data(), 0);
    //if still unknown, try to guess the file format from the file extension
    if (fif == FIF_UNKNOWN)
        fif = FreeImage_GetFIFFromFilename(filepath.data());
    //if still unkown, return failure
    if (fif == FIF_UNKNOWN)
        return false;

    //check that the plugin has reading capabilities and load the file
    if (FreeImage_FIFSupportsReading(fif))
        dib = FreeImage_Load(fif, filepath.data());
    //if the image failed to load, return failure
    if (!dib)
        return false;

    //retrieve the image data
    bits = FreeImage_GetBits(dib);
    //get the image width and height
    width = FreeImage_GetWidth(dib);
    height = FreeImage_GetHeight(dib);
    //if this somehow one of these failed (they shouldn't), return failure
    if ((bits == nullptr) || (width == 0) || (height == 0))
        return false;

    //generate an OpenGL texture ID for this texture
    glGenTextures(1, texID);
    //bind to the new texture ID
    glBindTexture(GL_TEXTURE_2D, *texID);
    //store the texture data for OpenGL use
    glTexImage2D(GL_TEXTURE_2D, level, internal_format, width, height, border, image_format, GL_UNSIGNED_BYTE, bits);
    //filter options
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    //Free FreeImage's copy of the data
    FreeImage_Unload(dib);

    //return success
    return true;
}
