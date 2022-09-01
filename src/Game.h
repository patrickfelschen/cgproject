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

class Game {
public:
    explicit Game(Camera* camera);

    virtual ~Game();

    void processKeyInput(int key, int action);

    void processMouseInput(float xpos, float ypos);

    void update(float deltaTime);

    void render();

private:
    UniformBuffer *uboMatrices;

    std::vector<Entity *> entities;
    std::vector<EnemyEntity *> targets;
    std::vector<StaticEntity *> magazineCases;
    std::vector<StaticEntity *> medicCases;
    Camera* camera;

    bool isAlive = true;

    void initNewGame();

    void checkTerrainCollision(Entity *entity, float groundOffset = 0.0f);

    bool checkPlayerCollision(Entity *entity, Camera *camera, float hitOffset) const;

    ObjectModel *gunModel;
    ObjectModel *ghostModel;
    ObjectModel *skyboxModel;
    ObjectModel *magazineCaseModel;
    ObjectModel *medicCaseModel;
    TerrainModel *terrainModel;

    GunEntity *gunEntity;
    SkyboxEntity *skyboxEntity;
    TerrainEntity *terrainEntity;

    ParticleManager *particleManager;
    TerrainManager *terrainManager;
    LightManager *lightManager;

    bool gameRestart = false;
    float targetSpeed = 1.0f;
    unsigned int hitCount = 0;
    unsigned int maxLife = 5;
    unsigned int life = 5;

    struct Matrices {
        Matrix projection;
        Matrix view;
        Vector3f camPos; float padding0;
    } matrices;
};


#endif //CG_GAME_H
