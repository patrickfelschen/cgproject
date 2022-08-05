//
// Created by Patrick on 01.08.2022.
//

#include "Game.h"
#include "entities/Orangutan.h"
#include "entities/SquirrelMonkey.h"
#include "shaders/PhongShader.h"

Game::Game(GLFWwindow &window, const Camera &camera) : window(window), camera(camera) {
    Shader *shader = new PhongShader();

    Model *orangutanModel = new ObjectModel(shader, "../assets/Objects/Orangutan.obj");
    Model *landscape = new ObjectModel(shader, "../assets/Objects/Terrain/model.obj");
    Model *manmodel = new ObjectModel(shader, "../assets/Objects/IronMan/IronMan.obj");

    Entity *monkey = new Orangutan(orangutanModel);
    Entity *terrain = new SquirrelMonkey(landscape);
    Entity *ironman = new Orangutan(manmodel);

    dynamic_cast<PhongShader*>(shader)->moveLight(Vector3f(2.0f, 5.0f, 0.0f));

    ironman->setPosition(0.0f, 0.0f, 0.0f);
    ironman->setScaling(0.001f);

//
//    entities.push_back(monkey);
//    entities.push_back(terrain);
    entities.push_back(ironman);
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
