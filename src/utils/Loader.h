//
// Created by Patrick on 01.08.2022.
//

#ifndef CG_LOADER_H
#define CG_LOADER_H

#include <string>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include "GL/glew.h"
#include "RGBImage.h"

class Loader {
public:
    static GLuint compileShaders(const char *vsFilePath, const char *fsFilePath);

    static void readImageFile(const char *filePath, RGBImage &outImage);

private:
    static void readShaderFile(const char *filePath, std::string &outFile);

    static void addShader(GLuint shaderProgramId, const char *shaderText, GLenum shaderType);

    std::unordered_map<const char *, std::string> shaderFileCache;
    std::unordered_map<const char *, RGBImage> imageFileCache;
};


#endif //CG_LOADER_H
