//
// Created by Patrick on 05.08.2022.
//

#include "PhongShader.h"

PhongShader::PhongShader() : Shader("../assets/shaders/shader.vert",
                                    "../assets/shaders/shader.frag") {}

void PhongShader::setUniforms(const Camera &camera) {
    Shader::setUniforms(camera);
    setUniform("lightPos", Vector3f(0.0f, -2.0f, 2.0f));
    setUniform("camPos", camera.getPosition());
}

PhongShader::~PhongShader() = default;
