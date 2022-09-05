//
// Created by Patrick on 31.08.2022.
//

#include "GunShader.h"

#define VERT "../assets/Shaders/gunShader.vert"
#define FRAG "../assets/Shaders/phongShader.frag"

GunShader::GunShader() : Shader(VERT, FRAG) {
    this->transform.identity();
}

/**
 * Transformations Matrix in den Shader laden
 */
void GunShader::setUniforms() {
    // Transformation
    setUniform("uTransform", transform);
}

GunShader::~GunShader() = default;
