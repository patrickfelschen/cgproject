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
    this->model->shader->setTransform(transformation);
    this->model->render();
}
