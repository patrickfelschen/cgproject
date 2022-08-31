//
// Created by Patrick on 01.08.2022.
//

#include "Game.h"
#include "buffers/UniformBuffer.h"
#include "managers/LightManager.h"
#include "shaders/GunShader.h"

#define TARGET_COUNT 35
#define PARTICLE_COUNT 400
#define MEDIC_CASE_COUNT 50
#define MAGAZINE_CASE_COUNT 20

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

UniformBuffer *uboMatrices;

Game::Game(Camera *camera) : camera(camera) {
    uboMatrices = new UniformBuffer(sizeof(Matrices), 0);
    matrices.projection = camera->getProj();
    uboMatrices->setSubData(offsetof(Matrices, projection), sizeof(Matrix), &matrices.projection.m);

    lightManager = new LightManager(camera);

    // Modelle
    magazineCaseModel = new ObjectModel(new PhongShader(), "../assets/Objects/MagazineCase/4VIOFB4XH3KJI43V6ILU5L0S5.obj");
    gunModel = new ObjectModel(new GunShader(), "../assets/Objects/Gun/ZE8FK2UU5PF8Y5F5777X34XII.obj");
    ghostModel = new ObjectModel(new PhongShader(), "../assets/Objects/Ghost/D4LM6XEKRW9PXSVHUEDQHY7OM.obj");
    skyboxModel = new ObjectModel(new PhongShader(), "../assets/Objects/SkyBox/skybox.obj");
    medicCaseModel = new ObjectModel(new PhongShader(), "../assets/Objects/MedicCase/8XK1NA3IKVGQHS9JM2IM2D2W4.obj");
    terrainModel = new TerrainModel(new TerrainShader());
    // Himmel
    skyboxEntity = new SkyboxEntity(skyboxModel);
    // Umgebung
    terrainEntity = new TerrainEntity(terrainModel);
    // Waffe
    gunEntity = new GunEntity(gunModel);

    entities.push_back(gunEntity);
    entities.push_back(terrainEntity);

    // MagazineCase
    for (unsigned int i = 0; i < MAGAZINE_CASE_COUNT; i++) {
        auto *entity = new StaticEntity(magazineCaseModel);
        entity->setPosition(Vector3f(terrainEntity->getRandomPosition(Vector3f(0.0f, 0.33f, 0.0f))));
        entity->setScaling(0.5f);
        entity->setRotation(Vector3f(0, Random::randFloat(0, 360), 0));
        magazineCases.push_back(entity);
    }
    // MedicCase
    for(unsigned int i = 0; i < MEDIC_CASE_COUNT; i++) {
        auto *entity = new StaticEntity(medicCaseModel);
        entity->setPosition(Vector3f(terrainEntity->getRandomPosition(Vector3f(0.0f, 0.275f, 0.0f))));
        entity->setScaling(0.5f);
        entity->setRotation(Vector3f(0, Random::randFloat(0, 360), 0));
        medicCases.push_back(entity);
    }
    // Skybox
    entities.push_back(skyboxEntity);
    // Ziele
    for (unsigned int i = 0; i < TARGET_COUNT; i++) {
        auto *entity = new EnemyEntity(ghostModel);
        entity->setPosition(terrainEntity->getRandomPosition(Vector3f(0.0f, 0.5f, 0.0f)));
        entity->setTargetPosition(camera->getPosition());
        targets.push_back(entity);
    }
    gunEntity->setTargets(targets);

    particleManager = new ParticleManager(PARTICLE_COUNT);
    terrainManager = new TerrainManager(terrainEntity, lightManager);
}

Game::~Game() {};

void Game::processKeyInput(int key, int action) {
    if (key == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        gunEntity->startShoot(*camera);
    }
    if (key == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
        gunEntity->endShoot();
    }
    if (key == GLFW_KEY_R && action == GLFW_PRESS) {
        gunEntity->reload();
    }
    if (!isAlive && (key == GLFW_KEY_SPACE && action == GLFW_PRESS)) {
        initNewGame();
    }
}

void Game::processMouseInput(float xpos, float ypos) {
    camera->handleMouseInputs(xpos, ypos);
}

void Game::update(float deltaTime) {
    if (isAlive) {
        // Kamera aktualisieren
        camera->update(deltaTime);
        // Alle Ziele aktualisieren
        for (EnemyEntity *entity: targets) {
            if (entity->hit) {
                particleManager->spawn(entity->getPosition(), Color(1.0f));
                entity->respawn(terrainEntity->getRandomPosition(Vector3f(0.0f, 1.2f, 0.0f)));
                hitCount++;
                if((hitCount % 5) == 0) {
                    targetSpeed += 0.05f;
                }
                // std::cout << "Treffer: " << hitCount << std::endl;
            }
            if (checkPlayerCollision(entity, camera, 0.4f)) {
                life--;
                isAlive = life > 0;

                particleManager->spawn(entity->getPosition(), Color(1.0f, 0.0f, 0.0f, 1.0f));
                entity->respawn(terrainEntity->getRandomPosition(Vector3f(0.0f, 1.2f, 0.0f)));

                // std::cout << "Contact, Life: " << life << std::endl;
            }

            checkTerrainCollision(entity, 0.2f);
            entity->setTargetPosition(camera->getPosition());
            entity->setSpeed(targetSpeed);
            entity->update(deltaTime);
        }
        // Alle MagazineCases aktualisieren
        for (StaticEntity *entity: magazineCases) {
            if(checkPlayerCollision(entity, camera, 1.0f)) {
                particleManager->spawn(entity->getPosition(), Color(0.0f, 0.0f, 1.0f, 1.0f));
                entity->setPosition(terrainEntity->getRandomPosition(Vector3f(0.0f, 0.33f, 0.0f)));
                gunEntity->addMagazines(2);
//            std::cout << "Added Magazine" << std::endl;
            }
            entity->update(deltaTime);
        }
        // Alle MedicCases aktualisieren
        for (StaticEntity *entity: medicCases) {
            if(checkPlayerCollision(entity, camera, 1.0f)) {
                particleManager->spawn(entity->getPosition(), Color(0.0f, 1.0f, 0.0f, 1.0f));
                entity->setPosition(terrainEntity->getRandomPosition(Vector3f(0.0f, 0.275f, 0.0f)));
                if(life < maxLife) life++;
            }
            entity->update(deltaTime);
        }
        // Alle Einheiten aktualisieren
        for (Entity *entity: entities) {
            entity->update(deltaTime);
        }

        particleManager->update(deltaTime);
        terrainManager->update(deltaTime);

        float playerHeight = terrainModel->getHeightOfTerrain(camera->getPosition().x, camera->getPosition().z);
        camera->setPosition(Vector3f(camera->getPosition().x, playerHeight + 1.0f, camera->getPosition().z));

        GUIManager::getInstance().updateScoreWindow(hitCount);
        GUIManager::getInstance().updateLifeWindow(life, maxLife);
        GUIManager::getInstance().drawFPSCounter();
    }
    else {
        char score[12];
        sprintf(score, "Score: %i", hitCount);
        GUIManager::getInstance().drawMainMenu(gameRestart, "Restart", "Game Over!", Color(1.0f, 0.0f, 0.0f, 1.0f), score);
        if (hitCount > Loader::getInstance().readScoreFromFile()) {
            Loader::getInstance().writeScoreToFile(hitCount);
        }
        if(gameRestart) {
            gameRestart = false;
            initNewGame();
        }
    }
}

void Game::render() {
    matrices.view = camera->getView();
    matrices.camPos = camera->getPosition();
    uboMatrices->setSubData(offsetof(Matrices, view), sizeof(Matrix), &matrices.view.m);
    uboMatrices->setSubData(offsetof(Matrices, camPos), sizeof(Vector3f), &matrices.camPos);

    lightManager->render();

    // Alle Ziele zeichnen
    for (EnemyEntity *entity: targets) {
        entity->render(*camera);
    }
    // Alle MagazineCases zeichnen
    for (StaticEntity *entity: magazineCases) {
        entity->render(*camera);
    }
    // Alle MedicCases zeichnen
    for(StaticEntity *entity: medicCases) {
        entity->render(*camera);
    }
    // Alle Einheiten zeichnen
    for (Entity *entity: entities) {
        entity->render(*camera);
    }
    particleManager->render(*camera);
    terrainManager->render(*camera);
}

void Game::checkTerrainCollision(Entity *entity, float groundOffset) {
    float height = terrainModel->getHeightOfTerrain(entity->getPosition().x, entity->getPosition().z);
    if (entity->getPosition().y <= (height + groundOffset)) {
        entity->setPosition(Vector3f(entity->getPosition().x, height + groundOffset, entity->getPosition().z));
    }
}

bool Game::checkPlayerCollision(Entity *entity, Camera *camera, float hitOffset) const {
    if (entity->getPosition().distanceTo(camera->getPosition()) <= hitOffset) return true;

    return false;
}

void Game::initNewGame() {
    this->isAlive = true;
    life = maxLife;
    hitCount = 0;
    gunEntity->setAmmo(30);
    gunEntity->setMagazines(5);

    // Gegner neu setzen
    for (EnemyEntity *entity: targets) {
        entity->respawn(terrainEntity->getRandomPosition(Vector3f(0.0f, 1.2f, 0.0f)));
    }
    // MagazineCases neu setzen
    for (StaticEntity *entity: magazineCases) {
        entity->setPosition(terrainEntity->getRandomPosition(Vector3f(0.0f, 0.33f, 0.0f)));
    }
    // MedicCases neu setzen
    for (StaticEntity *entity: medicCases) {
        entity->setPosition(terrainEntity->getRandomPosition(Vector3f(0.0f, 0.33f, 0.0f)));
    }

    camera->setPosition(Vector3f(0.0f, 0.0f, 0.0f));
}
