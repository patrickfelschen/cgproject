//
// Created by Patrick on 01.08.2022.
//

#include "Game.h"
#include "shaders/PhongShader.h"
#include "entities/GunEntity.h"
#include "entities/CoinEntity.h"
#include "models/TerrainModel.h"
#include "shaders/TerrainShader.h"
#include "entities/TerrainEntity.h"
#include "ParticleManager.h"
#include "entities/SkyboxEntity.h"

#define TARGET_COUNT 1

ObjectModel *garageModel;
ObjectModel *gunModel;
ObjectModel *coinModel;
ObjectModel *skyboxModel;
TerrainModel *terrainModel;

GunEntity *gunEntity;
Entity *garageEntity1;
Entity *garageEntity2;
Entity *garageEntity3;
Entity *garageEntity4;
SkyboxEntity *skyboxEntity;
Entity *terrainEntity;

ParticleManager *particleManager;

unsigned int hitCount = 0;

Game::Game(Camera *camera) : camera(camera) {

    // Modelle
    //garageModel = new ObjectModel(new PhongShader(), "../assets/Objects/Garage/MUW04SKJGJ052IRMJUCT9DJ5E.obj");
    gunModel = new ObjectModel(new PhongShader(), "../assets/Objects/Gun/ZE8FK2UU5PF8Y5F5777X34XII.obj");
    coinModel = new ObjectModel(new PhongShader(), "../assets/Objects/Coin/I89O58TBZ353I4X9ANHTRFF5K.obj");
    skyboxModel = new ObjectModel(new PhongShader(), "../assets/Objects/SkyBox/skybox.obj");
    terrainModel = new TerrainModel(new TerrainShader());
    // Coin Partikel
    particleManager = new ParticleManager(100);
    // Himmel
    skyboxEntity = new SkyboxEntity(skyboxModel);
    // Umgebung
    terrainEntity = new TerrainEntity(terrainModel);
    //terrainEntity->setPosition(0, -0.5, 0);
    // Waffe
    gunEntity = new GunEntity(gunModel);

    // Garagen
//    garageEntity1 = new Entity(garageModel);
//    garageEntity1->setScaling(2.0f);
//    garageEntity1->setPosition(3, 1, 3);
//
//    garageEntity2 = new Entity(garageModel);
//    garageEntity2->setScaling(2.0f);
//    garageEntity2->setPosition(-3, 1, 3);
//    garageEntity2->setRotationY(180);
//
//    garageEntity3 = new Entity(garageModel);
//    garageEntity3->setScaling(2.0f);
//    garageEntity3->setPosition(3, 1, -3);
//
//    garageEntity4 = new Entity(garageModel);
//    garageEntity4->setScaling(2.0f);
//    garageEntity4->setPosition(-3, 1, -3);
//    garageEntity4->setRotationY(180);

    entities.push_back(gunEntity);
//    entities.push_back(garageEntity1);
//    entities.push_back(garageEntity2);
//    entities.push_back(garageEntity3);
//    entities.push_back(garageEntity4);
    entities.push_back(skyboxEntity);
    entities.push_back(terrainEntity);

    // Ziele
    for (unsigned int i = 0; i < TARGET_COUNT; i++) {
        targets.push_back(new CoinEntity(coinModel));
    }

    gunEntity->setTargets(targets);

    srand(time(nullptr));
}

Game::~Game() {
    delete camera;
};

void Game::processKeyInput(int key, int action) {
    if (key == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        gunEntity->startShoot(*camera);
    }
    if (key == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
        gunEntity->endShoot();
    }
    if (key == GLFW_KEY_R && action == GLFW_PRESS) {
        gunEntity->reload();
    }
}

void Game::processMouseInput(float xpos, float ypos) { }

void Game::update(float deltaTime) {
    // Kamera aktualisieren
    camera->update(deltaTime);
    // Alle Ziele aktualisieren
    for (CoinEntity *entity: targets) {
        if (entity->hit) {
            particleManager->spawn(entity->getPosition());
            entity->respawn(camera->getPosition());
            hitCount++;
            std::cout << "Treffer: " << hitCount << std::endl;
        }
        entity->setTargetPosition(camera->getPosition());
        entity->update(deltaTime);
    }

    // Alle Einheiten aktualisieren
    for (Entity *entity: entities) {
        entity->update(deltaTime);
    }

    particleManager->update(deltaTime);

    float playerHeight = terrainModel->getHeightOfTerrain(camera->getPosition().x, camera->getPosition().z);
    camera->setPosition(Vector3f(camera->getPosition().x, playerHeight + 1.0f, camera->getPosition().z));

    GUIManager::getInstance().updateScoreWindow(hitCount);
}

void Game::render() {
    // Alle Ziele zeichnen
    for (CoinEntity *entity: targets) {
        entity->render(*camera);
    }
    // Alle Einheiten zeichnen
    for (Entity *entity: entities) {
        entity->render(*camera);
    }
    particleManager->render(*camera);
}
