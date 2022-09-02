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

void TerrainEntity::render() {
    this->model->shader->setTransform(transformation);
    this->model->render();
}

AABB TerrainEntity::getTransformedBoundingBox() const {
    return this->model->getBoundingBox().transform(transformation);
}

Vector3f TerrainEntity::getRandomPosition(Vector3f offset) const {
    float size = this->model->getSize() - 40;
    bool onTerrain; // immer true, da zwischen Size - 40
    float x = Random::randFloat(-size / 2, size / 2);
    float z = Random::randFloat(-size / 2, size / 2);
    float y = this->model->getHeightOfTerrain(x, z, onTerrain);
    return Vector3f(x, y, z) + offset;
}

float TerrainEntity::getHeightOfPosition(Vector3f position, bool &onTerrain) const {
    return this->model->getHeightOfTerrain(position.x, position.z, onTerrain);
}
