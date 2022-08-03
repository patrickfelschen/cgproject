//
// Created by Patrick on 01.08.2022.
//

#ifndef CG_LOADER_H
#define CG_LOADER_H

#include <string>
#include <iostream>
#include <fstream>
#include "GL/glew.h"

class Loader {
public:
    static GLuint compileShaders(const char *vsFilePath, const char *fsFilePath);

private:
    static void readFile(const char *filePath, std::string &outFile);

    static void addShader(GLuint shaderProgramId, const char *shaderText, GLenum shaderType);
};


#endif //CG_LOADER_H
