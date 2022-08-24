//
// Created by Patrick on 24.08.2022.
//

#include "TerrainEntity.h"

TerrainEntity::TerrainEntity(const TerrainModel *model) : Entity() {
    this->model = model;
}

TerrainEntity::~TerrainEntity() = default;

void TerrainEntity::update(float deltaTime) {
    Entity::update(deltaTime);
}

void TerrainEntity::render(const Camera &camera) {
    this->model->shader->setCameraPosition(camera.getPosition());
    this->model->shader->setProjection(camera.getProj());
    this->model->shader->setView(camera.getView());
    this->model->shader->setTransform(transformation);

    this->model->render();
}
