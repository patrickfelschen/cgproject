//
// Created by Patrick on 05.08.2022.
//

#include "PhongShader.h"

#define TO_RAD(deg) (deg * std::numbers::pi / 180.0)

#define VERT "../assets/shaders/phongShader.vert"
#define FRAG "../assets/shaders/phongShader.frag"

PhongShader::PhongShader() : Shader(VERT, FRAG) {
    this->transform.identity();
}

void PhongShader::setUniforms() {
    // Transformation
    setUniform("uTransform", transform);
}

void PhongShader::setTransform(const Matrix &t) {
    this->transform = t;
}

PhongShader::~PhongShader() = default;
