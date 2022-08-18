//
// Created by Patrick on 05.08.2022.
//

#include "PhongShader.h"

#define vert "../assets/shaders/phongShader.vert"
#define frag "../assets/shaders/phongShader.frag"

PhongShader::PhongShader() : Shader(vert, frag, true) {}

PhongShader::PhongShader(bool useView) : Shader(vert, frag, useView) {}

void PhongShader::setUniforms(const Camera &camera) {
    Shader::setUniforms(camera);
    // Kamera Position
    setUniform("uCamPos", camera.getPosition());
    // Licht
    Vector3f lightPos = Vector3f(-3.0f, 10.0f, 0.0f);
    Color light = Color(1.0f, 1.0f, 1.0f);
    Color lightDiffuse = light * 0.8;
    Color lightAmbient = lightDiffuse * 0.7f;
    Color lightSpecular = Color(1.0f, 1.0f, 1.0f);

    setUniform("uLight.position", lightPos);
    setUniform("uLight.ambient", lightAmbient);
    setUniform("uLight.diffuse", lightDiffuse);
    setUniform("uLight.specular", lightSpecular);
}

PhongShader::~PhongShader() = default;
