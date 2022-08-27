//
// Created by Patrick on 26.08.2022.
//

#include "TerrainManager.h"
#include "../entities/StaticEntity.h"
#include "../maths/Random.h"

#define STATIC_OBJECTS_COUNT 50

TerrainManager::TerrainManager(const TerrainEntity *terrainEntity) : terrainEntity(terrainEntity) {
    flowerYellowModel = new ObjectModel(new PhongShader(),"../assets/Objects/FlowerYellow/DR293GUXZXKK16RTKE4Y8HOCH.obj");
    flowerRedModel = new ObjectModel(new PhongShader(), "../assets/Objects/FlowerRed/XBV47D0X9MNPQYA15BSYICAXS.obj");
    woodModel = new ObjectModel(new PhongShader(), "../assets/Objects/Wood/BJWDXMOHII5I7VAGI8Q12YATN.obj");
    treeModel = new ObjectModel(new PhongShader(), "../assets/Objects/Tree01/N6TIYZO5D41STEOW4SQBKWRRG.obj");

    // Bäume
    for (unsigned int i = 0; i < STATIC_OBJECTS_COUNT; i++) {
        auto *entity = new StaticEntity(treeModel);
        entity->setPosition(terrainEntity->getRandomPosition(Vector3f(0.0f, 2.0f, 0.0f)));
        entity->setScaling(3.0f);
        entity->setRotation(Vector3f(0, Random::randFloat(0, 360), 0));
        entities.push_back(entity);
    }
    // Holz
    for (unsigned int i = 0; i < STATIC_OBJECTS_COUNT; i++) {
        auto *entity = new StaticEntity(woodModel);
        entity->setPosition(terrainEntity->getRandomPosition());
        entity->setScaling(0.5f);
        entity->setRotation(Vector3f(0, Random::randFloat(0, 360), 0));
        entities.push_back(entity);
    }
    // Blumen rot
    for (unsigned int i = 0; i < STATIC_OBJECTS_COUNT; i++) {
        auto *entity = new StaticEntity(flowerRedModel);
        entity->setPosition(terrainEntity->getRandomPosition(Vector3f(0.0f, 0.3f, 0.0f)));
        entity->setScaling(0.2f);
        entity->setRotation(Vector3f(0, Random::randFloat(0, 360), 0));
        entities.push_back(entity);
    }
    // Blumen gelb
    for (unsigned int i = 0; i < STATIC_OBJECTS_COUNT; i++) {
        auto *entity = new StaticEntity(flowerYellowModel);
        entity->setPosition(terrainEntity->getRandomPosition(Vector3f(0.0f, 0.3f, 0.0f)));
        entity->setScaling(0.2f);
        entity->setRotation(Vector3f(0, Random::randFloat(0, 360), 0));
        entities.push_back(entity);
    }
}

TerrainManager::~TerrainManager() {
    delete flowerYellowModel;
    delete flowerRedModel;
    delete woodModel;
    delete treeModel;
}

void TerrainManager::update(float deltaTime) {
    for (Entity *entity: entities) {
        entity->update(deltaTime);
    }
}

void TerrainManager::render(const Camera &camera) {
    for (Entity *entity: entities) {
        entity->render(camera);
    }
}