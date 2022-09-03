//
// Created by Patrick on 24.08.2022.
//

#include "ParticleShader.h"

#define VERT "../assets/shaders/particleShader.vert"
#define FRAG "../assets/shaders/particleShader.frag"

ParticleShader::ParticleShader() : Shader(VERT, FRAG) {
    this->color = Color(1.0f);
}

ParticleShader::~ParticleShader() = default;

void ParticleShader::setUniforms() {
    setUniform("uTransform", transform);
    setUniform("uColor", color);
}

void ParticleShader::setColor(const Color &c) {
    this->color = c;
}
