//
// Created by Patrick on 01.08.2022.
//

#include "Game.h"
#include "entities/Orangutan.h"
#include "entities/SquirrelMonkey.h"
#include "shaders/PhongShader.h"

Game::Game(GLFWwindow &window, const Camera &camera) : window(window), camera(camera) {
    Shader *shader = new PhongShader();

    Model *orangutanModel = new ObjectModel(shader, "../assets/Objects/scene/scene.obj");
    Model *squirrelMonkeyModel = new ObjectModel(shader, "../assets/Objects/SquirrelMonkey.OBJ");

    Entity *monkey = new Orangutan(orangutanModel);
    Entity *squirrelMonkey = new SquirrelMonkey(squirrelMonkeyModel);

    entities.push_back(monkey);
    entities.push_back(squirrelMonkey);
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
