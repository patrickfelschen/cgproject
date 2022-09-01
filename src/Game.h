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
#include "entities/EnemyEntity.h"
#include "shaders/PhongShader.h"
#include "entities/GunEntity.h"
#include "entities/EnemyEntity.h"
#include "models/TerrainModel.h"
#include "shaders/TerrainShader.h"
#include "entities/TerrainEntity.h"
#include "managers/ParticleManager.h"
#include "entities/SkyboxEntity.h"
#include "entities/StaticEntity.h"
#include "maths/Random.h"
#include "managers/TerrainManager.h"
#include "managers/SoundManager.h"
#include "entities/PlayerEntity.h"

class Game {
public:
    explicit Game(Camera* camera);

    virtual ~Game();

    void processKeyInput(int key, int action);

    void processMouseInput(float xpos, float ypos);

    void update(float deltaTime);

    void render();

private:
    Camera* camera;

    UniformBuffer *uboMatrices;

    std::vector<Entity *> entities;
    std::vector<EnemyEntity *> enemies;
    std::vector<StaticEntity *> magazineCases;
    std::vector<StaticEntity *> medicCases;

    void initModels();

    void initEntities();

    void initManagers();

    void initNewGame();

    ObjectModel *gunModel;
    ObjectModel *ghostModel;
    ObjectModel *skyboxModel;
    ObjectModel *magazineCaseModel;
    ObjectModel *medicCaseModel;
    TerrainModel *terrainModel;

    SkyboxEntity *skyboxEntity;
    TerrainEntity *terrainEntity;

    PlayerEntity *playerEntity;

    TerrainManager *terrainManager;
    LightManager *lightManager;

    bool gameRestart = false;
    float targetSpeed = 1.0f;

    struct Matrices {
        Matrix projection;
        Matrix view;
        Vector3f camPos; float padding0;
    } matrices;

};


#endif //CG_GAME_H
