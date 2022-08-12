//
// Created by Patrick on 01.08.2022.
// https://ogldev.org/www/tutorial04/tutorial04.html
//

#include "Loader.h"
#include "FreeImage.h"
#include "RGBImage.h"
#include <cassert>
#include <vector>

/**
 *
 * @param filePath
 * @param outFile
 * @return
 */
void Loader::readShaderFile(const char *filePath, std::string &outFile) {
    std::ifstream f(filePath);
    if (f.is_open()) {
        std::string line;
        while (std::getline(f, line)) {
            outFile.append(line);
            outFile.append("\n");
        }
        f.close();
        std::cout << "LOADER::READSHADERFILE: " << filePath << std::endl;
        return;
    } else {
        std::cerr << "ERROR::LOADER::READSHADERFILE: " << filePath << std::endl;
        exit(EXIT_SUCCESS);
    }
}

void Loader::readImageFile(const char *filePath, RGBImage &outImage) {
    // Prüfe den Dateityp, ob es sich um eine BitMap handelt
    FREE_IMAGE_FORMAT imageFormat = FreeImage_GetFileType(filePath, 0);

    if (imageFormat == FIF_UNKNOWN) {
        imageFormat = FreeImage_GetFIFFromFilename(filePath);
    }
    if (imageFormat == FIF_UNKNOWN) {
        std::cout << "WARNING::LOADER::READIMAGEFILE: Unbekanntes Dateiformat!" << std::endl;
    }
    FIBITMAP *pBitMap = FreeImage_Load(imageFormat, filePath);
    if (pBitMap == nullptr) {
        std::cout << "ERROR::LOADER::READIMAGEFILE: Dateiformat kann nicht geöffnet werden!" << std::endl;
        exit(EXIT_FAILURE);
    }

    FREE_IMAGE_TYPE type = FreeImage_GetImageType(pBitMap);
    assert(type == FIT_BITMAP);

    // Lese die Breite, Höhe und Bit pro Pixel der Datei aus.
    unsigned int width = FreeImage_GetWidth(pBitMap);
    unsigned int height = FreeImage_GetHeight(pBitMap);
    unsigned int bpp = FreeImage_GetBPP(pBitMap);
    assert(bpp == 16 || bpp == 24 || bpp == 32);

    // Speicherplatz für alle Pixel erstellen
    RGBImage image(width, height);

    // Speicherplatz für einzelnen Pixel erstellen
    RGBQUAD color;
    // Pixel Farbe auslesen und abspeichern
    for (unsigned int x = 0; x < width; x++) {
        for (unsigned int y = 0; y < width; y++) {
            FreeImage_GetPixelColor(pBitMap, x, y, &color);
            Color pixelColor = Color(color.rgbRed, color.rgbGreen, color.rgbBlue);
            if (bpp == 32) {
                pixelColor = Color(color.rgbRed, color.rgbGreen, color.rgbBlue, color.rgbReserved);
            }
            image.setPixelColor(x, y, pixelColor);
        }
    }

    // Speicherplatz freigeben
    FreeImage_Unload(pBitMap);

    std::cout << "LOADER::READIMAGEFILE: " << filePath << std::endl;
    outImage = image;
}

void Loader::addShader(GLuint shaderProgramId, const char *shaderText, GLenum shaderType) {
    GLuint shaderObject = glCreateShader(shaderType);
    if (shaderObject == 0) {
        std::cerr << "ERROR::ADDSHADER: Can not create shader type " << shaderType << std::endl;
        exit(EXIT_FAILURE);
    }
    const GLchar *p[1];
    p[0] = shaderText;

    GLint lengths[1];
    lengths[0] = (GLint) strlen(shaderText);

    glShaderSource(shaderObject, 1, p, lengths);
    glCompileShader(shaderObject);

    GLint success;
    glGetShaderiv(shaderObject, GL_COMPILE_STATUS, &success);

    if (!success) {
        GLchar infoLog[1024];
        glGetShaderInfoLog(shaderObject, 1024, nullptr, infoLog);
        std::cerr << "ERROR::ADDSHADER: " << infoLog << std::endl;
        exit(EXIT_FAILURE);
    }

    glAttachShader(shaderProgramId, shaderObject);
    glDeleteShader(shaderObject);
}

GLuint Loader::compileShaders(const char *vsFilePath, const char *fsFilePath) {
    GLuint shaderProgramId = glCreateProgram();
    if (shaderProgramId == 0) {
        std::cerr << "ERROR::COMPILESHADERS: Can not create shader program" << std::endl;
        exit(EXIT_FAILURE);
    }

    std::string vs, fs;

    Loader::readShaderFile(vsFilePath, vs);
    addShader(shaderProgramId, vs.c_str(), GL_VERTEX_SHADER);

    Loader::readShaderFile(fsFilePath, fs);
    addShader(shaderProgramId, fs.c_str(), GL_FRAGMENT_SHADER);

    GLint success = 0;
    GLchar errorLog[1024] = {0};

    glLinkProgram(shaderProgramId);

    glGetProgramiv(shaderProgramId, GL_LINK_STATUS, &success);
    if (success == 0) {
        glGetProgramInfoLog(shaderProgramId, sizeof(errorLog), nullptr, errorLog);
        std::cerr << "ERROR::COMPILESHADERS: Can not link shader program: " << errorLog << std::endl;
        exit(EXIT_FAILURE);
    }

    glValidateProgram(shaderProgramId);
    glGetProgramiv(shaderProgramId, GL_VALIDATE_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgramId, sizeof(errorLog), nullptr, errorLog);
        std::cerr << "ERROR::COMPILESHADERS: Invalid shader program: " << errorLog << std::endl;
        exit(EXIT_FAILURE);
    }

    glUseProgram(shaderProgramId);

    return shaderProgramId;
}