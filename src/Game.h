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
    explicit Game(Camera* camera);

    virtual ~Game();

    void processKeyInput(int key, int action);

    void processMouseInput(float xpos, float ypos);

    void update(float deltaTime);

    void render();



private:
    std::vector<Entity *> entities;
    std::vector<CoinEntity *> targets;
    Camera* camera;
};


#endif //CG_GAME_H
