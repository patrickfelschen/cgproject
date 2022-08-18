//
// Created by Patrick on 01.08.2022.
//

#ifndef CG_GAME_H
#define CG_GAME_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "utils/Camera.h"
#include "entities/Entity.h"
#include "entities/CoinEntity.h"

class Game {
public:
    explicit Game(GLFWwindow &window, const Camera &camera);

    virtual ~Game();

    void update(float deltaTime);

    void render();

private:
    GLFWwindow &window;
    Camera camera;
    std::vector<Entity *> entities;
    std::vector<CoinEntity *> targets;
};


#endif //CG_GAME_H
