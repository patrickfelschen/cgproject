//
// Created by Patrick on 01.08.2022.
//

#include "Game.h"
#include "entities/Orangutan.h"
#include "entities/SquirrelMonkey.h"
#include "shaders/PhongShader.h"
Entity *pistol;

Game::Game(GLFWwindow &window, const Camera &camera) : window(window), camera(camera) {
    Model *pistolModel = new ObjectModel(new PhongShader(), "../assets/Objects/Pistol/Pistol_02.obj");

    pistol = new SquirrelMonkey(pistolModel);
    Entity *pistol2 = new SquirrelMonkey(pistolModel);

    entities.push_back(pistol);
    entities.push_back(pistol2);
}

void Game::update(float deltaTime) {
    camera.update(deltaTime);

    pistol->setPosition(0, 10, 0);

    for (Entity *entity: entities) {
        entity->update(deltaTime);
    }
}

void Game::render() {
    for (Entity *entity: entities) {
        entity->render(camera);
    }
}
