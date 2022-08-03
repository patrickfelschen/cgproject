//
// Created by Patrick on 01.08.2022.
//

#include "Game.h"

Game::Game(GLFWwindow &window, const Camera &camera) : window(window), camera(camera) {
    Shader shader = Shader("../assets/shaders/shader.vert", "../assets/shaders/shader.frag");
    Renderable *renderable = new Model(shader);
    renderables.push_back(renderable);
}

void Game::update(float deltaTime) {

    camera.update(deltaTime);

    for (Renderable *renderable: this->renderables) {
        renderable->update(deltaTime);
    }
}

void Game::render() {
    for (Renderable *renderable: this->renderables) {
        renderable->render(camera);
    }
}
