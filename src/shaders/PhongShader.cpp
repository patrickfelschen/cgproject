//
// Created by Patrick on 05.08.2022.
//

#include "PhongShader.h"

PhongShader::PhongShader() : Shader("../assets/shaders/shader.vert",
                                    "../assets/shaders/shader.frag",
                                    true) {
    lightPos = Vector3f(0.0f, 1.0f, 0.0f);
}

PhongShader::PhongShader(bool useView) : Shader("../assets/shaders/shader.vert",
                                                "../assets/shaders/shader.frag",
                                                useView) {
    lightPos = Vector3f(0.0f, 1.0f, 0.0f);
}

void PhongShader::setUniforms(const Camera &camera) {
    Shader::setUniforms(camera);
    setUniform("lightPos", lightPos);
    setUniform("camPos", camera.getPosition());
}

PhongShader::~PhongShader() = default;
