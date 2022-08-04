//
// Created by Patrick on 02.08.2022.
//

#include "Shader.h"

Shader::Shader(const char *vsFilePath, const char *fsFilePath) : vsFilePath(vsFilePath), fsFilePath(fsFilePath) {
    this->modelTransform.identity();
    this->compile();
}

void Shader::compile() {
    // Shader laden und kompilieren
    id = Loader::compileShaders(vsFilePath, fsFilePath);
}

void Shader::setUniforms(const Camera &camera) {
    setUniform("projection", camera.getProj());
    setUniform("view", camera.getView());
    setUniform("transform", modelTransform);
    setUniform("lightPos", Vector3f(0.0f, -2.0f, 2.0f));
    setUniform("camPos", camera.getPosition());
}

void Shader::activate(const Camera &camera) {
    if (id <= 0) {
        std::cerr << "ERROR::SHADER: can not activate shader" << std::endl;
        exit(EXIT_FAILURE);
    }
    // Shader aktivieren
    glUseProgram(id);

    // Uniform setzen
    setUniforms(camera);
}

void Shader::deactivate() const {
    glUseProgram(0);
}

void Shader::setUniform(const char *name, int value) {
    glUniform1i(getUniformLocation(name), value);
}

void Shader::setUniform(const char *name, float value) {
    glUniform1f(getUniformLocation(name), value);
}

void Shader::setUniform(const char *name, const Vector3f &value) {
    glUniform3f(getUniformLocation(name), value.x, value.y, value.z);
}

void Shader::setUniform(const char *name, const Matrix &value) {
    glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, value.m);
}

GLint Shader::getUniformLocation(const char *name) {
    if (uniformLocationCache.find(name) != uniformLocationCache.end()) {
        return uniformLocationCache[name];
    }

    GLint locationId = glGetUniformLocation(id, name);
    if (locationId == -1) {
        std::cerr << "ERROR::SHADER: can not find uniform location" << std::endl;
        exit(EXIT_FAILURE);
    }
    uniformLocationCache[name] = locationId;

    return locationId;
}

void Shader::setModelTransform(const Matrix &mt) {
    this->modelTransform = mt;
}

Shader::~Shader() = default;
