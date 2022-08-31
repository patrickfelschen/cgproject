//
// Created by Patrick on 01.08.2022.
// https://ogldev.org/www/tutorial04/tutorial04.html
//

#include "Loader.h"


void Loader::readShaderFile(const std::string &filePath, std::string &outFile) {
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
        std::cout << "WARNING::LOADER::READIMAGEFILE: Unbekanntes Dateiformat! " << filePath << std::endl;
    }
    FIBITMAP *pBitMap = FreeImage_Load(imageFormat, filePath);
    if (pBitMap == nullptr) {
        std::cout << "ERROR::LOADER::READIMAGEFILE: Dateiformat kann nicht geoeffnet werden! " << filePath << std::endl;
        exit(EXIT_FAILURE);
    }

    FreeImage_FlipVertical(pBitMap);

    FREE_IMAGE_TYPE type = FreeImage_GetImageType(pBitMap);
    assert(type == FIT_BITMAP);

    // Lese die Breite, Höhe und Bit pro Pixel der Datei aus.
    unsigned int width = FreeImage_GetWidth(pBitMap);
    unsigned int height = FreeImage_GetHeight(pBitMap);
    unsigned int bpp = FreeImage_GetBPP(pBitMap);
    assert(bpp == 1 || bpp == 8 || bpp == 16 || bpp == 24 || bpp == 32);
    GLenum format = GL_RGBA;
//    if(bpp == 1) format = GL_RED;
//    if(bpp == 8) format = GL_RED;
//    if(bpp == 16) format = GL_RGB;
//    if(bpp == 24) format = GL_RGB;
//    if(bpp == 32) format = GL_RGBA;
    // Speicherplatz für alle Pixel erstellen
    RGBImage image(width, height, format);
    // Speicherplatz für einzelnen Pixel erstellen
    RGBQUAD color;
    // Pixel Farbe auslesen und abspeichern
    for (unsigned int x = 0; x < width; x++) {
        for (unsigned int y = 0; y < width; y++) {
            FreeImage_GetPixelColor(pBitMap, x, y, &color);
            Color pixelColor;
            if (bpp == 32) {
                pixelColor = Color(color.rgbRed, color.rgbGreen, color.rgbBlue, color.rgbReserved);
            } else {
                pixelColor = Color(color.rgbRed, color.rgbGreen, color.rgbBlue);
            }
            image.setPixelColor(x, y, pixelColor);
        }
    }

    // Speicherplatz freigeben
    FreeImage_Unload(pBitMap);

    std::cout << "LOADER::READIMAGEFILE: " << filePath << std::endl;
    outImage = image;
}

void Loader::addShader(const std::string &shaderText, GLuint id, GLenum shaderType) {
    GLuint shaderObject = glCreateShader(shaderType);
    if (shaderObject == 0) {
        std::cerr << "ERROR::SHADER::ADDSHADER: Can not create shader type " << shaderType << std::endl;
        exit(EXIT_FAILURE);
    }
    const GLchar *p[1];
    p[0] = shaderText.c_str();

    GLint lengths[1];
    lengths[0] = (GLint) strlen(shaderText.c_str());

    glShaderSource(shaderObject, 1, p, lengths);
    glCompileShader(shaderObject);

    GLint success;
    glGetShaderiv(shaderObject, GL_COMPILE_STATUS, &success);

    if (!success) {
        GLchar infoLog[1024];
        glGetShaderInfoLog(shaderObject, 1024, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::ADDSHADER: " << infoLog << std::endl;
        exit(EXIT_FAILURE);
    }

    glAttachShader(id, shaderObject);
    glDeleteShader(shaderObject);
}

GLuint Loader::compileShaders(const std::string& vsFilePath, const std::string& fsFilePath) {
    std::string shaderName = vsFilePath + fsFilePath;

    if (shaderCache.find(shaderName) != shaderCache.end()) {
        std::cout << "LOADER::COMPILESHADERS: ShaderCache HIT" << std::endl;
        return shaderCache[shaderName];
    }

    GLuint id = glCreateProgram();
    if (id == 0) {
        std::cerr << "ERROR::SHADER::COMPILESHADERS: Can not create shader program" << std::endl;
        exit(EXIT_FAILURE);
    }

    std::string vs, fs;

    Loader::readShaderFile(vsFilePath, vs);
    addShader(vs, id, GL_VERTEX_SHADER);

    Loader::readShaderFile(fsFilePath, fs);
    addShader(fs, id, GL_FRAGMENT_SHADER);

    std::cout << "SHADER::COMPILED: " << vsFilePath << " " << fsFilePath << std::endl;

    GLint success = 0;
    GLchar errorLog[1024] = {0};

    glLinkProgram(id);

    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if (success == 0) {
        glGetProgramInfoLog(id, sizeof(errorLog), nullptr, errorLog);
        std::cerr << "ERROR::SHADER::COMPILESHADERS: Can not link shader program: " << errorLog << std::endl;
        exit(EXIT_FAILURE);
    }

    glValidateProgram(id);
    glGetProgramiv(id, GL_VALIDATE_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(id, sizeof(errorLog), nullptr, errorLog);
        std::cerr << "ERROR::SHADER::COMPILESHADERS: Invalid shader program: " << errorLog << std::endl;
        exit(EXIT_FAILURE);
    }
    shaderCache[shaderName] = id;
    glUseProgram(id);
    return id;
}

void Loader::writeScoreToFile(unsigned int score) {
    std::ofstream scoreFile;
    scoreFile.open("../assets/score.txt");
    scoreFile << score;
    scoreFile.close();
}

unsigned int Loader::readScoreFromFile() {
    unsigned int score;
    std::ifstream  scoreFile;
    scoreFile.open("../assets/score.txt");
    scoreFile >> score;
    scoreFile.close();
    return score;
}
