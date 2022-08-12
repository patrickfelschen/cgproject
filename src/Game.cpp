//
// Created by Patrick on 01.08.2022.
//

#include "Game.h"
#include "shaders/PhongShader.h"
#include "entities/GunEntity.h"
#include "entities/CoinEntity.h"

Entity *gun;
Entity *garage;
Model *coinModel;
Entity *skybox;
Game::Game(GLFWwindow &window, const Camera &camera) : window(window), camera(camera) {

    Model *garageModel = new ObjectModel(new PhongShader(), "../assets/Objects/Garage/MUW04SKJGJ052IRMJUCT9DJ5E.obj");
    Model *gunModel = new ObjectModel(new PhongShader(), "../assets/Objects/Gun/ZE8FK2UU5PF8Y5F5777X34XII.obj");
    coinModel = new ObjectModel(new PhongShader(), "../assets/Objects/Coin/I89O58TBZ353I4X9ANHTRFF5K.obj");
    Model *skyboxModel = new ObjectModel(new PhongShader(), "../assets/Objects/SkyBox/skybox.obj");

    gun = new GunEntity(gunModel);
    garage = new Entity(garageModel);
    skybox = new Entity(skyboxModel);


    //entities.push_back(gun);
    entities.push_back(garage);
    entities.push_back(skybox);

    srand(time(0));
}

void Game::update(float deltaTime) {
    camera.update(deltaTime);

    for (Entity *entity: entities) {
        entity->update(deltaTime);
    }
}

void Game::render() {
    if(entities.size() < 15) {
        if((rand() % 100) < 1) {
            Entity *newEnt = new CoinEntity(coinModel);
            entities.push_back(newEnt);
        }
    }

    for (Entity *entity: entities) {
        entity->render(camera);
    }
}
