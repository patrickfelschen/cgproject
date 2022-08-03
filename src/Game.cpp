//
// Created by Patrick on 01.08.2022.
//

#include "Game.h"

Game::Game(GLFWwindow &window, const Camera &camera) : window(window), camera(camera) {
    Shader shader = Shader("../assets/shaders/shader.vert", "../assets/shaders/shader.frag");
    Texture texture = Texture("../assets/Objects/grass.bmp");
    auto *renderable1 = new Model(shader, texture);
    auto *renderable2 = new Model(shader, texture);
    renderable1->setPosition(Vector3f(0.0f, 0.0f, 1.0f));
    renderable2->setPosition(Vector3f(2.0f, 1.0f, 0.0f));
    renderables.push_back(renderable1);
    renderables.push_back(renderable2);
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
