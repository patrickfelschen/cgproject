//
// Created by Patrick on 05.08.2022.
//

#include "PhongShader.h"

#define VERT "../assets/Shaders/phongShader.vert"
#define FRAG "../assets/Shaders/phongShader.frag"

PhongShader::PhongShader() : Shader(VERT, FRAG) {
    this->transform.identity();
}

/**
 * Transformations Matrix in den Shader laden
 */
void PhongShader::setUniforms() {
    // Transformation
    setUniform("uTransform", transform);
}

PhongShader::~PhongShader() = default;
