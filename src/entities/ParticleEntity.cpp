//
// Created by Patrick on 24.08.2022.
//

#include "ParticleEntity.h"

ParticleEntity::ParticleEntity(const ParticleModel *model) {
    this->model = model;
    this->color = Color(0.0f);
    this->life = 0.0f;
}

ParticleEntity::~ParticleEntity() = default;

void ParticleEntity::update(float deltaTime) {
    life -= deltaTime;
    color.a -= deltaTime / maxLife;
    Entity::update(deltaTime);
}

void ParticleEntity::render(const Camera &camera) {
    this->model->shader->setProjection(camera.getProj());
    this->model->shader->setView(camera.getView());
    this->model->shader->setTransform(transformation);
    this->model->shader->setColor(color);
    this->model->shader->setScale(scale);

    this->model->render();
}

const Color &ParticleEntity::getColor() const {
    return color;
}

void ParticleEntity::setColor(const Color &c) {
    this->color = c;
}

float ParticleEntity::getLife() const {
    return life;
}

void ParticleEntity::setLife(float l) {
    this->maxLife = l;
    this->life = l;
}

void ParticleEntity::setScale(float s) {
    this->scale = s;
}