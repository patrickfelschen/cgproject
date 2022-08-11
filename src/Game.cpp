//
// Created by Patrick on 01.08.2022.
//

#include "Game.h"
#include "entities/Orangutan.h"
#include "entities/SquirrelMonkey.h"
#include "shaders/PhongShader.h"
Entity *gun;
Entity *garage;
Game::Game(GLFWwindow &window, const Camera &camera) : window(window), camera(camera) {

    Model *garageModel = new ObjectModel(new PhongShader(), "../assets/Objects/Garage/MUW04SKJGJ052IRMJUCT9DJ5E.obj");
    Model *gunModel = new ObjectModel(new PhongShader(), "../assets/Objects/Gun/ZE8FK2UU5PF8Y5F5777X34XII.obj");

    gun = new SquirrelMonkey(gunModel);
    garage = new Orangutan(garageModel);

    entities.push_back(gun);
    entities.push_back(garage);

}

void Game::update(float deltaTime) {
    camera.update(deltaTime);

    for (Entity *entity: entities) {
        entity->update(deltaTime);
    }
}

void Game::render() {
    for (Entity *entity: entities) {
        entity->render(camera);
    }
}
