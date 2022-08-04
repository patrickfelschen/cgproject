//
// Created by Patrick on 01.08.2022.
//

#ifndef CG_GAME_H
#define CG_GAME_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "models/Model.h"
#include "utils/Camera.h"

class Game {
public:
    explicit Game(GLFWwindow &window, const Camera &camera);

    ~Game() = default;

    void update(float deltaTime);

    void render();

private:
    GLFWwindow &window;
    Camera camera;
    std::vector<Model> models;
};


#endif //CG_GAME_H
