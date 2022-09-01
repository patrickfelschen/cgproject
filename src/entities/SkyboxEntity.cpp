//
// Created by Patrick on 24.08.2022.
//

#include "SkyboxEntity.h"

SkyboxEntity::SkyboxEntity(const ObjectModel *model) : model(model) {
    setScaling(1.0f);
}

SkyboxEntity::~SkyboxEntity() = default;

void SkyboxEntity::render() {
    this->model->shader->setTransform(transformation);
    this->model->render();
}

AABB SkyboxEntity::getTransformedBoundingBox() const {
    return this->model->getBoundingBox().transform(transformation);
}
