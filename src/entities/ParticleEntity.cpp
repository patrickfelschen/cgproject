//
// Created by Patrick on 24.08.2022.
//

#include "ParticleEntity.h"

ParticleEntity::ParticleEntity(const ParticleModel *model) {
    this->model = model;
    this->color = Color(0.0f);
    this->maxLife = 0.0f;
    this->life = maxLife;
}

ParticleEntity::~ParticleEntity() = default;

/**
 * Verringert über die Zeit das Leben und den Alphawert der Farbe
 * @param deltaTime Zeitunterschied zum letzten Frame
 */
void ParticleEntity::update(float deltaTime) {
    life -= deltaTime;
    color.a -= deltaTime / maxLife;
    Entity::update(deltaTime);
}

void ParticleEntity::render() {
    this->model->shader->setTransform(transformation);
    this->model->shader->setColor(color);
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

/**
 * Liefert transformierte BoundingBox des Entity Models zurück
 * @return BoundingBox des Models
 */
AABB ParticleEntity::getTransformedBoundingBox() const {
    return this->model->getBoundingBox().transform(transformation);
}
