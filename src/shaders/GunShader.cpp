//
// Created by Patrick on 31.08.2022.
//

#include "GunShader.h"

#define VERT "../assets/shaders/gunShader.vert"
#define FRAG "../assets/shaders/phongShader.frag"

GunShader::GunShader() : Shader(VERT, FRAG) {}

GunShader::~GunShader() = default;

void GunShader::setUniforms() {
    // Transformation
    setUniform("uTransform", transform);
}
