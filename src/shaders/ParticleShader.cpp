//
// Created by Patrick on 24.08.2022.
//

#include "ParticleShader.h"

#define VERT "../assets/shaders/particleShader.vert"
#define FRAG "../assets/shaders/particleShader.frag"

ParticleShader::ParticleShader() : Shader(VERT, FRAG) {
    this->projection.identity();
    this->transform.identity();
    this->view.identity();
    this->scale = 0.01f;
    this->color = Color(1.0f);
}

ParticleShader::~ParticleShader() = default;

void ParticleShader::setUniforms() {
    setUniform("uProjection", projection);
    setUniform("uTransform", transform);
    setUniform("uView", view);
    setUniform("uColor", color);
    setUniform("uScale", scale);
}

void ParticleShader::setTransform(const Matrix &t) {
    this->transform = t;
}

void ParticleShader::setView(const Matrix &v) {
    this->view = v;
}

void ParticleShader::setProjection(const Matrix &p) {
    this->projection = p;
}

void ParticleShader::setColor(const Color &c) {
    this->color = c;
}

void ParticleShader::setScale(float s) {
    this->scale = s;
}
