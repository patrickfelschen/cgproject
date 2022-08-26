//
// Created by Patrick on 01.08.2022.
// https://stackoverflow.com/a/1008289
//

#ifndef CG_LOADER_H
#define CG_LOADER_H

#include <string>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include "GL/glew.h"
#include "RGBImage.h"
#include "FreeImage.h"
#include "RGBImage.h"
#include <cassert>
#include <vector>

class Loader {

public:
    static Loader &getInstance() {
        static Loader instance;
        return instance;
    }

    Loader(Loader const &) = delete;

    void operator=(Loader const &) = delete;

    void readImageFile(const char *filePath, RGBImage &outImage);

    void readShaderFile(const std::string &filePath, std::string &outFile);

    GLuint compileShaders(const std::string &vsFilePath, const std::string &fsFilePath);

private:
    Loader() = default;

    std::unordered_map<std::string, GLuint> shaderCache;

    void addShader(const std::string &shaderText, GLuint id, GLenum shaderType);
};

#endif //CG_LOADER_H
