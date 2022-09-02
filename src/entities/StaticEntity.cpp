//
// Created by Patrick on 25.08.2022.
//

#include "StaticEntity.h"

StaticEntity::StaticEntity(const ObjectModel *model, const TerrainEntity *terrainEntity) {
    this->model = model;
    this->terrainEntity = terrainEntity;
}

StaticEntity::~StaticEntity() = default;

void StaticEntity::update(float deltaTime) {
    Entity::update(deltaTime);
}

void StaticEntity::render() {
    this->model->shader->setTransform(transformation);
    this->model->render();
}

void StaticEntity::respawn() {
    Vector3f newPos = terrainEntity->getRandomPosition(spawnOffset);
    setPosition(newPos);
}

AABB StaticEntity::getTransformedBoundingBox() const {
    return this->model->getBoundingBox().transform(transformation);
}

void StaticEntity::setSpawnOffset(const Vector3f &spawnOffset) {
    StaticEntity::spawnOffset = spawnOffset;
}

