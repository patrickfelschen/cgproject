//
// Created by Patrick on 25.08.2022.
//

#include "StaticEntity.h"

StaticEntity::StaticEntity(const ObjectModel *model) : model(model) {
}

StaticEntity::~StaticEntity() = default;

void StaticEntity::update(float deltaTime) {
    Entity::update(deltaTime);
}

void StaticEntity::render(const Camera &camera) {
    this->model->shader->setCameraPosition(camera.getPosition());
    this->model->shader->setProjection(camera.getProj());
    this->model->shader->setView(camera.getView());
    this->model->shader->setTransform(transformation);
    this->model->render();
}
