//
// Created by Patrick on 01.08.2022.
//

#include "Game.h"

#define TARGET_COUNT 35
#define PARTICLE_COUNT 400
#define CASE_COUNT 20

ObjectModel *gunModel;
ObjectModel *coinModel;
ObjectModel *skyboxModel;
ObjectModel *caseModel;

TerrainModel *terrainModel;

GunEntity *gunEntity;
SkyboxEntity *skyboxEntity;
TerrainEntity *terrainEntity;

ParticleManager *particleManager;
TerrainManager *terrainManager;

unsigned int hitCount = 0;
unsigned int maxLife = 5;
unsigned int life = 5;

Game::Game(Camera *camera) : camera(camera) {
    // Modelle
    caseModel = new ObjectModel(new PhongShader(), "../assets/Objects/Case/4VIOFB4XH3KJI43V6ILU5L0S5.obj");
    gunModel = new ObjectModel(new PhongShader(), "../assets/Objects/Gun/ZE8FK2UU5PF8Y5F5777X34XII.obj");
    coinModel = new ObjectModel(new PhongShader(), "../assets/Objects/Ghost/D4LM6XEKRW9PXSVHUEDQHY7OM.obj");
    skyboxModel = new ObjectModel(new PhongShader(), "../assets/Objects/SkyBox/skybox.obj");
    terrainModel = new TerrainModel(new TerrainShader());
    // Himmel
    skyboxEntity = new SkyboxEntity(skyboxModel);
    // Umgebung
    terrainEntity = new TerrainEntity(terrainModel);
    // Waffe
    gunEntity = new GunEntity(gunModel);

    entities.push_back(gunEntity);
    entities.push_back(terrainEntity);

    // Case
    for (unsigned int i = 0; i < CASE_COUNT; i++) {
        auto *entity = new StaticEntity(caseModel);
        entity->setPosition(Vector3f(terrainEntity->getRandomPosition(Vector3f(0.0f, 0.33f, 0.0f))));
        entity->setScaling(0.5f);
        entity->setRotation(Vector3f(0, Random::randFloat(0, 360), 0));
        cases.push_back(entity);
    }
    // Skybox
    entities.push_back(skyboxEntity);
    // Ziele
    for (unsigned int i = 0; i < TARGET_COUNT; i++) {
        auto *entity = new EnemyEntity(coinModel);
        entity->setPosition(terrainEntity->getRandomPosition(Vector3f(0.0f, 0.5f, 0.0f)));
        entity->setTargetPosition(camera->getPosition());
        targets.push_back(entity);
    }
    gunEntity->setTargets(targets);

    particleManager = new ParticleManager(PARTICLE_COUNT);
    terrainManager = new TerrainManager(terrainEntity);
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
    if(!isAlive && (key == GLFW_KEY_SPACE && action == GLFW_PRESS)) {
        initNewGame();
    }
}

void Game::processMouseInput(float xpos, float ypos) {
    camera->handleMouseInputs(xpos, ypos);
}

void Game::update(float deltaTime) {
    if(isAlive) {
        // Kamera aktualisieren
        camera->update(deltaTime);
        // Alle Ziele aktualisieren
        for (EnemyEntity *entity: targets) {
            if (entity->hit) {
                particleManager->spawn(entity->getPosition(), Color(1.0f));
                entity->respawn(terrainEntity->getRandomPosition(Vector3f(0.0f, 1.2f, 0.0f)));
                hitCount++;
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
            entity->update(deltaTime);
        }
        // Alle Cases aktualisieren
        for (StaticEntity *entity: cases) {
            if(checkPlayerCollision(entity, camera, 1.0f)) {
                particleManager->spawn(entity->getPosition(), Color(0.0f, 0.0f, 1.0f, 1.0f));
                entity->setPosition(terrainEntity->getRandomPosition(Vector3f(0.0f, 0.33f, 0.0f)));
                gunEntity->addMagazines(2);
//            std::cout << "Added Magazine" << std::endl;
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
        GUIManager::getInstance().drawInfo("Game over! Press Space to restart.");
    }
}

void Game::render() {
    // Alle Ziele zeichnen
    for (EnemyEntity *entity: targets) {
        entity->render(*camera);
    }
    // Alle Cases zeichnen
    for (StaticEntity *entity: cases) {
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

    // Gegner neu setzen
    for (EnemyEntity *entity: targets) {
        entity->respawn(terrainEntity->getRandomPosition(Vector3f(0.0f, 1.2f, 0.0f)));
    }
    // Cases neu setzen
    for (StaticEntity *entity: cases) {
        entity->setPosition(terrainEntity->getRandomPosition(Vector3f(0.0f, 0.33f, 0.0f)));
    }

    camera->setPosition(Vector3f(0.0f, 0.0f, 0.0f));
}
