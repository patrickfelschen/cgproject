//
// Created by Patrick on 24.08.2022.
//

#include "SkyboxEntity.h"

SkyboxEntity::SkyboxEntity(const ObjectModel *model) : model(model) {
    setScaling(1.0f);
}

SkyboxEntity::~SkyboxEntity() = default;

void SkyboxEntity::render(const Camera &camera) {
    this->model->shader->setCameraPosition(camera.getPosition());
    this->model->shader->setProjection(camera.getProj());
    this->model->shader->setView(camera.getView());
    this->model->shader->setTransform(transformation);
    this->model->render();
}
