//
// Created by Patrick on 26.08.2022.
//

#include "TerrainManager.h"
#include "../entities/StaticEntity.h"
#include "../maths/Random.h"

#define STATIC_OBJECTS_COUNT 100
#define LIGHT_POLE_COUNT 20

/**
 * Lädt Modelle der Objekte, die sich auf dem Terrain befinden und plaziert diese zufällig
 * @param terrainEntity Wird für die Positionsberechnung der StaticEntities benötigt
 * @param lightManager Fügt den Lightpoles Licht hinzu
 */
TerrainManager::TerrainManager(const TerrainEntity *terrainEntity, LightManager *lightManager) :
        terrainEntity(terrainEntity), lightManager(lightManager) {
    flowerYellowModel = new ObjectModel(
            new PhongShader(),
            "../assets/Objects/FlowerYellow/DR293GUXZXKK16RTKE4Y8HOCH.obj"
    );
    flowerRedModel = new ObjectModel(
            new PhongShader(),
            "../assets/Objects/FlowerRed/XBV47D0X9MNPQYA15BSYICAXS.obj"
    );
    woodModel = new ObjectModel(
            new PhongShader(),
            "../assets/Objects/Wood/BJWDXMOHII5I7VAGI8Q12YATN.obj"
    );
    treeModel = new ObjectModel(
            new PhongShader(),
            "../assets/Objects/Tree01/N6TIYZO5D41STEOW4SQBKWRRG.obj"
    );
    lightPoleModel = new ObjectModel(
            new PhongShader(),
            "../assets/Objects/LightPole/CLADLXMYVP3UCZ3ZVD9QWPQGZ.obj"
    );

    // Bäume
    for (unsigned int i = 0; i < STATIC_OBJECTS_COUNT; i++) {
        auto *entity = new StaticEntity(treeModel, terrainEntity);
        entity->setScaling(3.0f);
        entity->setRotation(Vector3f(0, Random::randFloat(0, 360), 0));
        entity->setSpawnOffset(Vector3f(0.0f, 2.0f, 0.0f));
        entity->respawn();
        entities.push_back(entity);
    }
    // Holz
    for (unsigned int i = 0; i < STATIC_OBJECTS_COUNT; i++) {
        auto *entity = new StaticEntity(woodModel, terrainEntity);
        entity->setScaling(0.5f);
        entity->setRotation(Vector3f(0, Random::randFloat(0, 360), 0));
        entity->setSpawnOffset(Vector3f(0.0f, 0.1f, 0.0f));
        entity->respawn();
        entities.push_back(entity);
    }
    // Blumen rot
    for (unsigned int i = 0; i < STATIC_OBJECTS_COUNT; i++) {
        auto *entity = new StaticEntity(flowerRedModel, terrainEntity);
        entity->setScaling(0.2f);
        entity->setRotation(Vector3f(0, Random::randFloat(0, 360), 0));
        entity->setSpawnOffset(Vector3f(0.0f, 0.3f, 0.0f));
        entity->respawn();
        entities.push_back(entity);
    }
    // Blumen gelb
    for (unsigned int i = 0; i < STATIC_OBJECTS_COUNT; i++) {
        auto *entity = new StaticEntity(flowerYellowModel, terrainEntity);
        entity->setScaling(0.2f);
        entity->setRotation(Vector3f(0, Random::randFloat(0, 360), 0));
        entity->setSpawnOffset(Vector3f(0.0f, 0.3f, 0.0f));
        entity->respawn();
        entities.push_back(entity);
    }
    // Laternen
    for (unsigned int i = 0; i < LIGHT_POLE_COUNT; i++) {
        auto *entity = new StaticEntity(lightPoleModel, terrainEntity);
        entity->setScaling(1.0f);
        entity->setRotation(Vector3f(0, Random::randFloat(0, 360), 0));
        entity->setSpawnOffset(Vector3f(0.0f, 1.2f, 0.0f));
        entity->respawn();
        // Licht positionieren
        Vector3f lightPosOffset = Vector3f(0, 0.6f, 0);
        lightManager->addPoint(entity->getPosition() + lightPosOffset);
        entities.push_back(entity);
    }
}

TerrainManager::~TerrainManager() {
    for (Entity *entity: entities) {
        delete entity;
    }
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

void TerrainManager::render() {
    for (Entity *entity: entities) {
        entity->render();
    }
}
