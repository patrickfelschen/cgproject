//
// Created by Patrick on 05.08.2022.
//

#include "PhongShader.h"

PhongShader::PhongShader() : Shader("../assets/shaders/phongShader.vert",
                                    "../assets/shaders/phongShader.frag",
                                    true) {
    lightPos = Vector3f(0.0f, 1.0f, 0.0f);
}

PhongShader::PhongShader(bool useView) : Shader("../assets/shaders/phongShader.vert",
                                                "../assets/shaders/phongShader.frag",
                                                useView) {
    lightPos = Vector3f(0.0f, 1.0f, 0.0f);
}

void PhongShader::setUniforms(const Camera &camera) {
    Shader::setUniforms(camera);
    setUniform("uLightPos", lightPos);
    setUniform("uCamPos", camera.getPosition());
}

PhongShader::~PhongShader() = default;
