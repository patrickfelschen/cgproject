//
// Created by Patrick on 05.08.2022.
//

#include "PhongShader.h"

PhongShader::PhongShader() : Shader("../assets/shaders/shader.vert",
                                    "../assets/shaders/shader.frag") {
    lightPos = Vector3f(-5.0f, 15.0f, -10.0f);
}

void PhongShader::setUniforms(const Camera &camera) {
    Shader::setUniforms(camera);
    setUniform("lightPos", lightPos);
    setUniform("camPos", camera.getPosition());
}

void PhongShader::moveLight(const Vector3f &v) {
    lightPos = v;
}

PhongShader::~PhongShader() = default;
