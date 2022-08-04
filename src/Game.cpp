//
// Created by Patrick on 01.08.2022.
//

#include "Game.h"

Game::Game(GLFWwindow &window, const Camera &camera) : window(window), camera(camera) {
    Shader shader = Shader("../assets/shaders/shader.vert", "../assets/shaders/shader.frag");
    Model model = Model(shader);

    model.loadMesh("../assets/Objects/Orangutan.obj");

    model.setPosition(Vector3f(0.0f, 0.0f, 3.0f));
    model.setScale(0.1f);

    models.push_back(model);
}

void Game::update(float deltaTime) {

    camera.update(deltaTime);

    for (auto &model: models) {
        model.update(deltaTime);
    }
}

void Game::render() {
    for (auto &model: models) {
        model.render(camera);
    }
}
