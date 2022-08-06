//
// Created by Patrick on 01.08.2022.
//

#include "Game.h"
#include "entities/Orangutan.h"
#include "entities/SquirrelMonkey.h"
#include "shaders/PhongShader.h"

Game::Game(GLFWwindow &window, const Camera &camera) : window(window), camera(camera) {
    Shader *shader = new PhongShader();

    Model *nanosuitModel = new ObjectModel(shader, "../assets/Objects/Nanosuit/TTURDKN8VOY7P4PVHSULB36RF.obj");
    Model *gunModel = new ObjectModel(shader, "../assets/Objects/Gun/ZE8FK2UU5PF8Y5F5777X34XII.obj");

    Entity *nanosuit = new Orangutan(nanosuitModel);
    Entity *gun = new SquirrelMonkey(gunModel);

    gun->setScaling(1.0f);

    entities.push_back(gun);
    entities.push_back(nanosuit);

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
