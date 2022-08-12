//
// Created by Patrick on 01.08.2022.
// https://ogldev.org/www/tutorial04/tutorial04.html
//

#include "Loader.h"

/**
 *
 * @param filePath
 * @param outFile
 * @return
 */
void Loader::readFile(const char *filePath, std::string &outFile) {
    std::ifstream f(filePath);
    if (f.is_open()) {
        std::string line;
        while (std::getline(f, line)) {
            outFile.append(line);
            outFile.append("\n");
        }
        f.close();
        std::cout << filePath << std::endl;
        return;
    } else {
        std::cerr << "ERROR::READFILE: " << filePath << std::endl;
        exit(EXIT_SUCCESS);
    }
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

    Loader::readFile(vsFilePath, vs);
    addShader(shaderProgramId, vs.c_str(), GL_VERTEX_SHADER);

    Loader::readFile(fsFilePath, fs);
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