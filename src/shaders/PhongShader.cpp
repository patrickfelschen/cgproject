//
// Created by Patrick on 05.08.2022.
//

#include "PhongShader.h"

#define vert "../assets/shaders/phongShader.vert"
#define frag "../assets/shaders/phongShader.frag"

PhongShader::PhongShader() : Shader(vert, frag, true) {
    lightPos = Vector3f(0.0f, 1.0f, 0.0f);
}

PhongShader::PhongShader(bool useView) : Shader(vert, frag, useView) {
    lightPos = Vector3f(0.0f, 1.0f, 0.0f);
}

void PhongShader::setUniforms(const Camera &camera) {
    Shader::setUniforms(camera);
    setUniform("uLightPos", lightPos);
    setUniform("uCamPos", camera.getPosition());
    setUniform("uMaterial.ambientColor", Color(0.0f, 0.0f, 0.0f));
    setUniform("uMaterial.diffuseColor", Color(1.0f, 1.0f, 1.0f));
    setUniform("uMaterial.specularColor", Color(0.3f, 0.3f, 0.3f));
    setUniform("uMaterial.shininess", 10.0f);
}

PhongShader::~PhongShader() = default;
