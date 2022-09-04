//
// Created by Patrick on 25.08.2022.
//

#include "StaticEntity.h"

/**
 * Erstellt eine Statische Einheit, welche positioniert wird und
 * keine weitere Bewegung im Spiel hat
 * @param model Modell der Einheit
 * @param terrainEntity Terrain, auf welchem die Einheit positioniert werden kann
 */
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

/**
 * Positioniert die Einheit auf einem zufälligen Ort auf dem Terrain
 */
void StaticEntity::respawn() {
    Vector3f newPos = terrainEntity->getRandomPosition(spawnOffset);
    setPosition(newPos);
}

/**
 * Positionsänderung, damit Einheit richtig auf dem Terrain platziert ist
 * @param spawnOffset Verschiebung
 */
void StaticEntity::setSpawnOffset(const Vector3f &spawnOffset) {
    StaticEntity::spawnOffset = spawnOffset;
}

AABB StaticEntity::getTransformedBoundingBox() const {
    return this->model->getBoundingBox().transform(transformation);
}
