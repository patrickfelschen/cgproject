//
// Created by Patrick on 24.08.2022.
//

#include "ParticleShader.h"

#define VERT "../assets/Shaders/particleShader.vert"
#define FRAG "../assets/Shaders/particleShader.frag"

ParticleShader::ParticleShader() : Shader(VERT, FRAG) {
    this->color = Color(1.0f);
}

ParticleShader::~ParticleShader() = default;

/**
 * Transformations Matrix und Farbe in den Shader laden
 */
void ParticleShader::setUniforms() {
    setUniform("uTransform", transform);
    setUniform("uColor", color);
}

void ParticleShader::setColor(const Color &c) {
    this->color = c;
}
