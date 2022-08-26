//
// Created by Patrick on 24.08.2022.
//

#include "TerrainEntity.h"
#include "../maths/Random.h"

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

Vector3f TerrainEntity::getRandomPosition(Vector3f offset) const {
    float x = Random::randFloat(-100, 100);
    float z = Random::randFloat(-100, 100);
    float y = this->model->getHeightOfTerrain(x, z);
    return Vector3f(x,y,z) + offset;
}
