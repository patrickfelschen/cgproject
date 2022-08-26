//
// Created by Patrick on 02.08.2022.
// https://youtu.be/gDtHL6hy9R8
//

#include "Shader.h"


Shader::Shader(const char *vsFilePath, const char *fsFilePath) {
    this->vsFilePath = vsFilePath;
    this->fsFilePath = fsFilePath;
    this->id = Loader::getInstance().compileShaders(vsFilePath, fsFilePath);
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
