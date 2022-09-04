//
// Created by Patrick on 02.08.2022.
// Quelle: https://youtu.be/gDtHL6hy9R8
//

#include "Shader.h"

/**
 * Lädt Vertex- und Fragment-Shader
 * @param vsFilePath Pfad zum Vertex-Shader
 * @param fsFilePath Pfad zum Fragment-Shader
 */
Shader::Shader(const char *vsFilePath, const char *fsFilePath) {
    this->vsFilePath = vsFilePath;
    this->fsFilePath = fsFilePath;
    this->transform.identity();
    this->id = Loader::getInstance().compileShaders(vsFilePath, fsFilePath);
}

/**
 * Shader aktivieren und alle definierten Uniforms setzen
 */
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

/**
 * Shader deaktivieren
 */
void Shader::deactivate() const {
    glUseProgram(0);
}

void Shader::setTransform(const Matrix &t) {
    this->transform = t;
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

/**
 * Liefert die Position einer Uniform-Variable
 * Quelle: https://youtu.be/gDtHL6hy9R8?t=1040
 * @param name Bezeichnung der Uniform
 * @return ID der Uniform
 */
GLint Shader::getUniformLocation(const std::string &name) {
    // Prüfung, ob Uniform Location schon im Cache vorhanden ist
    if (uniformLocationCache.find(name) != uniformLocationCache.end()) {
        //std::cout << "Cache HIT" << std::endl;
        return uniformLocationCache[name];
    }
    // Uniform in Shader finden
    GLint locationId = glGetUniformLocation(id, name.c_str());
    if (locationId == -1) {
        std::cerr << "WARNING::SHADER::GETUNIFORMLOCATION: "
                  << fsFilePath << ": can not find location: "
                  << name << std::endl;
    }
    // Uniform Location zu Cache hinzufügen
    uniformLocationCache[name] = locationId;
    return locationId;
}

Shader::~Shader() = default;
