//
// Created by Patrick on 05.08.2022.
//

#include "PhongShader.h"

#define VERT "../assets/shaders/phongShader.vert"
#define FRAG "../assets/shaders/phongShader.frag"

PhongShader::PhongShader() : Shader(VERT, FRAG) {
    this->transform.identity();
}

void PhongShader::setUniforms() {
    // Transformation
    setUniform("uTransform", transform);
}

PhongShader::~PhongShader() = default;
