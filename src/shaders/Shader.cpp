//
// Created by Patrick on 02.08.2022.
//

#include "Shader.h"

Shader::Shader(const char *vsFilePath, const char *fsFilePath) : vsFilePath(vsFilePath), fsFilePath(fsFilePath) {
    this->modelTransform.identity();
    this->compile();
    this->queryUniforms();
}

void Shader::compile() {
    // Shader laden und kompilieren
    shaderProgramId = Loader::compileShaders(vsFilePath, fsFilePath);
}

void Shader::queryUniforms() {
    // Uniform Locations ermitteln
    projectionLoc = getUniformLocation("projection");
    viewLoc = getUniformLocation("view");
    transformLoc = getUniformLocation("transform");
    lightPosLoc = getUniformLocation("lightPos");
    camPosLoc = getUniformLocation("camPos");
}

void Shader::activate(const Camera &camera) const {
    if (shaderProgramId <= 0) {
        std::cerr << "ERROR::SHADER: can not activate shader" << std::endl;
        exit(EXIT_FAILURE);
    }
    // Shader aktivieren
    glUseProgram(shaderProgramId);

    // Uniform setzen
    setUniform(projectionLoc, camera.getProj());
    setUniform(viewLoc, camera.getView());
    setUniform(transformLoc, modelTransform);
    setUniform(lightPosLoc, Vector3f(0.0f, -2.0f, 2.0f));
    setUniform(camPosLoc, camera.getPosition());
}

void Shader::deactivate() const {
    glUseProgram(0);
}

void Shader::setUniform(GLint locationId, int value) const {
    glUniform1i(locationId, value);
}

void Shader::setUniform(GLint locationId, float value) const {
    glUniform1f(locationId, value);
}

void Shader::setUniform(GLint locationId, const Vector3f &value) const {
    glUniform3f(locationId, value.x, value.y, value.z);
}

void Shader::setUniform(GLint locationId, const Matrix &value) const {
    glUniformMatrix4fv(locationId, 1, GL_FALSE, value.m);
}

GLint Shader::getUniformLocation(const char *uniform) const {
    GLint locationId = glGetUniformLocation(shaderProgramId, uniform);
//    if (locationId == -1) {
//        std::cerr << "ERROR::SHADER: can not find uniform location" << std::endl;
//        exit(EXIT_FAILURE);
//    }
    return locationId;
}

void Shader::setModelTransform(const Matrix &mt) {
    this->modelTransform = mt;
}

Shader::~Shader() = default;
