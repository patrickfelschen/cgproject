//
// Created by Patrick on 01.08.2022.
//

#include "Game.h"
#include "shaders/PhongShader.h"
#include "entities/GunEntity.h"
#include "entities/CoinEntity.h"
#include "models/Model.h"
#include "models/ObjectModel.h"
#include "utils/Terrain.h"
#include "shaders/TerrainShader.h"

Entity *gun;
Entity *garage;
Model *coinModel;
Entity *skybox;
Terrain *terrain;

Game::Game(GLFWwindow &window, const Camera &camera) : window(window), camera(camera) {

    Model *garageModel = new ObjectModel(new PhongShader(), "../assets/Objects/Garage/MUW04SKJGJ052IRMJUCT9DJ5E.obj");
    Model *gunModel = new ObjectModel(new PhongShader(false), "../assets/Objects/Gun/ZE8FK2UU5PF8Y5F5777X34XII.obj");
    coinModel = new ObjectModel(new PhongShader(), "../assets/Objects/Coin/I89O58TBZ353I4X9ANHTRFF5K.obj");
    Model *skyboxModel = new ObjectModel(new PhongShader(), "../assets/Objects/SkyBox/skybox.obj");

    //terrain = new Terrain(new TerrainShader());

    gun = new GunEntity(gunModel);
    garage = new Entity(garageModel);
    skybox = new Entity(skyboxModel);

    entities.push_back(gun);
    entities.push_back(garage);
    entities.push_back(skybox);

    srand(time(nullptr));
}

void Game::update(float deltaTime) {
    camera.update(deltaTime);

    //terrain->update(deltaTime);

    for (Entity *entity: entities) {
        entity->update(deltaTime);
    }
}

void Game::render() {
    if (entities.size() < 15) {
        if ((rand() % 100) < 1) {
            Entity *newEnt = new CoinEntity(coinModel);
            entities.push_back(newEnt);
        }
    }

    //terrain->render(camera);

    for (Entity *entity: entities) {
        entity->render(camera);
    }


}
