//
// Created by Patrick on 02.08.2022.
// https://youtu.be/gDtHL6hy9R8
//

#include "Shader.h"


Shader::Shader(const char *vsFilePath, const char *fsFilePath) {
    this->vsFilePath = vsFilePath;
    this->fsFilePath = fsFilePath;
    compileShaders();
}

void Shader::addShader(const char *shaderText, GLenum shaderType) const {
    GLuint shaderObject = glCreateShader(shaderType);
    if (shaderObject == 0) {
        std::cerr << "ERROR::SHADER::ADDSHADER: Can not create shader type " << shaderType << std::endl;
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
        std::cerr << "ERROR::SHADER::ADDSHADER: " << infoLog << std::endl;
        exit(EXIT_FAILURE);
    }

    glAttachShader(id, shaderObject);
    glDeleteShader(shaderObject);
}

void Shader::compileShaders() {
    id = glCreateProgram();
    if (id == 0) {
        std::cerr << "ERROR::SHADER::COMPILESHADERS: Can not create shader program" << std::endl;
        exit(EXIT_FAILURE);
    }

    std::string vs, fs;

    Loader::readShaderFile(vsFilePath, vs);
    addShader(vs.c_str(), GL_VERTEX_SHADER);

    Loader::readShaderFile(fsFilePath, fs);
    addShader(fs.c_str(), GL_FRAGMENT_SHADER);

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

    glUseProgram(id);
}

void Shader::activate() {
    if (id <= 0) {
        std::cerr << "ERROR::SHADER::ACTIVATE can not activate shader" << std::endl;
        exit(EXIT_FAILURE);
    }
    // Shader aktivieren
    glUseProgram(id);
    // Uniform setzen
    setUniforms();
}

void Shader::deactivate() const {
    glUseProgram(0);
}

void Shader::setUniform(const std::string &name, int value) {
    glUniform1i(getUniformLocation(name), value);
}

void Shader::setUniform(const std::string &name, float value) {
    glUniform1f(getUniformLocation(name), value);
}

void Shader::setUniform(const std::string &name, const Vector3f &value) {
    glUniform3f(getUniformLocation(name), value.x, value.y, value.z);
}

void Shader::setUniform(const std::string &name, const Color &value) {
    glUniform4f(getUniformLocation(name), value.r, value.g, value.b, value.a);
}

void Shader::setUniform(const std::string &name, const Matrix &value) {
    glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, value.m);
}

GLint Shader::getUniformLocation(const std::string &name) {
    if (uniformLocationCache.find(name) != uniformLocationCache.end()) {
        //std::cout << "Cache HIT" << std::endl;
        return uniformLocationCache[name];
    }
    GLint locationId = glGetUniformLocation(id, name.c_str());
    if (locationId == -1) {
        std::cerr << "WARNING::SHADER::GETUNIFORMLOCATION: "
                  << fsFilePath << ": can not find uniform location: "
                  << name << std::endl;
        //exit(EXIT_FAILURE);
    }
    uniformLocationCache[name] = locationId;
    return locationId;
}


Shader::~Shader() = default;
