//
// Created by Patrick on 24.08.2022.
//

#include "ParticleEntity.h"

ParticleEntity::ParticleEntity(const ParticleModel *model) {
    this->model = model;
    this->color = Color(1.0f);
    this->offset = Vector3f();
    this->life = 10.0f;
    this->velocity = Vector3f();
}

ParticleEntity::~ParticleEntity() = default;

void ParticleEntity::update(float deltaTime) {
    Entity::update(deltaTime);
}

void ParticleEntity::render(const Camera &camera) {
    this->model->shader->setCameraPosition(camera.getPosition());
    this->model->shader->setProjection(camera.getProj());
    this->model->shader->setView(camera.getView());
    this->model->shader->setTransform(transformation);
    this->model->shader->setColor(color);
    this->model->shader->setOffset(offset);

    this->model->render();
}
