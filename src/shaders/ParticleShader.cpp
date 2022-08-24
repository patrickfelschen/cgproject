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
    this->offset = Vector3f();
    this->color = Color(1.0f);
}

ParticleShader::~ParticleShader() = default;

void ParticleShader::setUniforms() {
    setUniform("uProjection", projection);
    //setUniform("uTransform", transform);
    //setUniform("uView", view);

    // Kamera Position
    //setUniform("uCamPos", cameraPosition);
    setUniform("uOffset", offset);
    setUniform("uColor", color);
}

const Matrix &ParticleShader::getTransform() const {
    return transform;
}

void ParticleShader::setTransform(const Matrix &transform) {
    ParticleShader::transform = transform;
}

const Matrix &ParticleShader::getView() const {
    return view;
}

void ParticleShader::setView(const Matrix &view) {
    ParticleShader::view = view;
}

const Matrix &ParticleShader::getProjection() const {
    return projection;
}

void ParticleShader::setProjection(const Matrix &projection) {
    ParticleShader::projection = projection;
}

const Vector3f &ParticleShader::getCameraPosition() const {
    return cameraPosition;
}

void ParticleShader::setCameraPosition(const Vector3f &cameraPosition) {
    ParticleShader::cameraPosition = cameraPosition;
}

const Vector3f &ParticleShader::getOffset() const {
    return offset;
}

void ParticleShader::setOffset(const Vector3f &offset) {
    ParticleShader::offset = offset;
}

const Color &ParticleShader::getColor() const {
    return color;
}

void ParticleShader::setColor(const Color &color) {
    ParticleShader::color = color;
}
