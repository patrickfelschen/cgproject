//
// Created by Patrick on 01.08.2022.
//

#include "Game.h"
#include "shaders/PhongShader.h"
#include "entities/GunEntity.h"
#include "entities/CoinEntity.h"
#include "entities/BulletEntity.h"
#include "models/TerrainModel.h"
#include "shaders/TerrainShader.h"

Model *garageModel;
Model *gunModel;
Model *coinModel;
Model *skyboxModel;
Model *terrainModel;

GunEntity *gunEntity;
Entity *garageEntity;
Entity *skyboxEntity;
Entity *terrainEntity;

Game::Game(GLFWwindow &window, const Camera &camera) : window(window), camera(camera) {
    garageModel = new ObjectModel(new PhongShader(), "../assets/Objects/Garage/MUW04SKJGJ052IRMJUCT9DJ5E.obj");
    gunModel = new ObjectModel(new PhongShader(false), "../assets/Objects/Gun/ZE8FK2UU5PF8Y5F5777X34XII.obj");
    coinModel = new ObjectModel(new PhongShader(), "../assets/Objects/Coin/I89O58TBZ353I4X9ANHTRFF5K.obj");
    skyboxModel = new ObjectModel(new PhongShader(), "../assets/Objects/SkyBox/skybox.obj");
    terrainModel = new TerrainModel(new TerrainShader());

    gunEntity = new GunEntity(gunModel, window);
    garageEntity = new Entity(garageModel);
    skyboxEntity = new Entity(skyboxModel);
    terrainEntity = new Entity(terrainModel);
    terrainEntity->setPosition(0, -0.5, 0);

    entities.push_back(gunEntity);
    entities.push_back(garageEntity);
    entities.push_back(skyboxEntity);
    entities.push_back(terrainEntity);

    srand(time(0));
}

Game::~Game() {
    delete garageModel;
    delete gunModel;
    delete coinModel;
    delete skyboxModel;
    delete terrainModel;
    delete gunEntity;
    delete garageEntity;
    delete skyboxEntity;
    delete terrainEntity;
}

void Game::update(float deltaTime) {
    camera.update(deltaTime);

    for (Entity *entity: entities) {
        entity->update(deltaTime);
    }

    for (Entity *entity: targets) {
        entity->update(deltaTime);
    }
}

void Game::render() {
    if(targets.size() < 15) {
        if((rand() % 100) < 1) {
            CoinEntity *newEnt = new CoinEntity(coinModel);
            targets.push_back(newEnt);
            gunEntity->setTargets(&targets);
        }
    }

    for (Entity *entity: entities) {
        entity->render(camera);
    }

    for (Entity *entity: targets) {
        entity->render(camera);
    }
}
