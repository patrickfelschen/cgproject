//
// Created by Patrick on 01.08.2022.
//

#include "Game.h"
#include "buffers/UniformBuffer.h"
#include "managers/LightManager.h"
#include "shaders/GunShader.h"

#define ENEMY_COUNT 50
#define MEDIC_CASE_COUNT 50
#define MAGAZINE_CASE_COUNT 20

Game::Game(Camera *camera) : camera(camera) {
    // Uniform Buffer inizialisieren
    this->uboMatrices = new UniformBuffer(sizeof(Matrices), 0);
    // Projektion in Uniform Buffer laden
    this->matrices.projection = camera->getProj();
    this->uboMatrices->setSubData(offsetof(Matrices, projection), sizeof(Matrix), &matrices.projection);
    // Modelle laden
    this->initModels();
    // Einheiten laden
    this->initEntities();
    // Manager laden
    this->initManagers();
}

/**
 * Lädt einmalig alle Objekt Dateien
 */
void Game::initModels() {
    magazineCaseModel = new ObjectModel(
            new PhongShader(),
            "../assets/Objects/MagazineCase/4VIOFB4XH3KJI43V6ILU5L0S5.obj"
    );
    gunModel = new ObjectModel(
            new GunShader(),
            "../assets/Objects/Gun/ZE8FK2UU5PF8Y5F5777X34XII.obj"
    );
    ghostModel = new ObjectModel(
            new PhongShader(),
            "../assets/Objects/Ghost/D4LM6XEKRW9PXSVHUEDQHY7OM.obj"
    );
    skyboxModel = new ObjectModel(
            new PhongShader(),
            "../assets/Objects/SkyBox/skybox.obj"
    );
    medicCaseModel = new ObjectModel(
            new PhongShader(),
            "../assets/Objects/MedicCase/8XK1NA3IKVGQHS9JM2IM2D2W4.obj"
    );
    terrainModel = new TerrainModel(new TerrainShader());
}

/**
 * Erstellt Einheiten aus den geladenen Models
 */
void Game::initEntities() {
    // Umgebung
    terrainEntity = new TerrainEntity(terrainModel);
    entities.push_back(terrainEntity);
    // MagazineCase
    for (unsigned int i = 0; i < MAGAZINE_CASE_COUNT; i++) {
        auto *entity = new StaticEntity(magazineCaseModel, terrainEntity);
        entity->setScaling(0.5f);
        entity->setRotation(Vector3f(0, Random::randFloat(0, 360), 0));
        entity->setSpawnOffset(Vector3f(0.0, 0.33f, 0.0f));
        entity->respawn();
        magazineCases.push_back(entity);
    }
    // MedicCase
    for (unsigned int i = 0; i < MEDIC_CASE_COUNT; i++) {
        auto *entity = new StaticEntity(medicCaseModel, terrainEntity);
        entity->setScaling(0.5f);
        entity->setRotation(Vector3f(0, Random::randFloat(0, 360), 0));
        entity->setSpawnOffset(Vector3f(0.0, 0.175f, 0.0f));
        entity->respawn();
        medicCases.push_back(entity);
    }
    // Gegner
    for (unsigned int i = 0; i < ENEMY_COUNT; i++) {
        auto *entity = new EnemyEntity(ghostModel, terrainEntity);
        entity->setScaling(0.2f);
        entity->setTargetPosition(camera->getPosition());
        entity->respawn();
        enemies.push_back(entity);
    }
    // Waffe
    auto *gunEntity = new GunEntity(gunModel);
    // Spieler
    playerEntity = new PlayerEntity(camera, terrainEntity);
    playerEntity->setGunEntity(gunEntity);
    playerEntity->setEnemies(enemies);
    playerEntity->setMagazineCases(magazineCases);
    playerEntity->setMedicCases(medicCases);
    // Himmel
    skyboxEntity = new SkyboxEntity(skyboxModel);
    entities.push_back(skyboxEntity);
}

/**
 * Initialisiert Manager, welche gewissen Funktionen bündeln
 */
void Game::initManagers() {
    lightManager = new LightManager(camera);
    terrainManager = new TerrainManager(terrainEntity, lightManager);
}

/**
 * Initialisiert ein neues Spiel
 */
void Game::initNewGame() {
    this->playerEntity->init();

    // Gegner neu setzen
    for (EnemyEntity *entity: enemies) {
        entity->setMaxLife(1);
        entity->setSpeed(Random::randFloat(1.0f, 2.0f));
        entity->respawn();
    }
    // MagazineCases neu setzen
    for (StaticEntity *entity: magazineCases) {
        entity->respawn();
    }
    // MedicCases neu setzen
    for (StaticEntity *entity: medicCases) {
        entity->respawn();
    }

    camera->setPosition(Vector3f(0.0f, 0.0f, 0.0f));
}

/**
 * Wertet Benutzereingaben aus
 * @param key betätigte Taste
 * @param action zustand der Taste
 */
void Game::processKeyInput(int key, int action) {
    if (key == GLFW_MOUSE_BUTTON_LEFT) {
        if (action == GLFW_PRESS) {
            playerEntity->startShoot();
        }
        if (action == GLFW_RELEASE) {
            playerEntity->endShoot();
        }
    }
    if (key == GLFW_KEY_R && action == GLFW_PRESS) {
        playerEntity->reload();
    }
}

/**
 * Wertet Mouse-Bewegungen des Benutzers aus
 * @param xpos x-Position der Maus
 * @param ypos y-Position der Maus
 */
void Game::processMouseInput(float xpos, float ypos) {
    camera->handleMouseInputs(xpos, ypos);
}

/**
 * Aktualisierung des Spiels, wird pro Frame ausgeführt
 * @param deltaTime Zeitunterschied zum letzten Frame
 */
void Game::update(float deltaTime) {
    if (playerEntity->isAlive()) {
        // Spieler ist am Leben

        // Kamera aus Terrain positionieren
        bool onTerrain;
        float playerY = terrainModel->getHeightOfTerrain(
                camera->getPosition().x,
                camera->getPosition().z,
                onTerrain
        );
        camera->setPosition(Vector3f(camera->getPosition().x, playerY + 1.2f, camera->getPosition().z));

        // Kamera aktualisieren
        camera->update(deltaTime);
        SoundManager::getInstance().setListenerPos(camera);
        // Spieler aktualisieren
        playerEntity->update(deltaTime);
        // Alle Einheiten aktualisieren
        for (Entity *entity: entities) {
            entity->update(deltaTime);
        }
        // Terrain Einheiten aktualisieren
        terrainManager->update(deltaTime);

        GUIManager::getInstance().drawFPSCounter();
    } else {
        // Game Over Menu anzeigen
        char score[12];
        sprintf(score, "Punkte: %i", playerEntity->getHitCount());

        GUIManager::getInstance().drawMainMenu(
                gameRestart,
                "Neustart", "Verloren!",
                Color(1.0f, 0.0f, 0.0f, 1.0f),
                score
        );
        // Neuen Highscore in Datei abspeichern
        if (playerEntity->getHitCount() > Loader::getInstance().readScoreFromFile()) {
            Loader::getInstance().writeScoreToFile(playerEntity->getHitCount());
        }
        // Spiel neu starten wenn Button betätigt
        if (gameRestart) {
            gameRestart = false;
            initNewGame();
        }
    }
}

/**
 * Darstellung des Spiels, wird pro Frame nach update(...) ausgeführt
 */
void Game::render() {
    // View Matrix und Camera Position in Uniform Buffer laden (pro Frame)
    matrices.view = camera->getView();
    matrices.camPos = camera->getPosition();
    uboMatrices->setSubData(offsetof(Matrices, view), sizeof(Matrix), &matrices.view);
    uboMatrices->setSubData(offsetof(Matrices, camPos), sizeof(Vector3f), &matrices.camPos);

    lightManager->render();
    playerEntity->render();

    // Alle Ziele zeichnen
    for (EnemyEntity *entity: enemies) {
        entity->render();
    }
    // Alle MagazineCases zeichnen
    for (StaticEntity *entity: magazineCases) {
        entity->render();
    }
    // Alle MedicCases zeichnen
    for (StaticEntity *entity: medicCases) {
        entity->render();
    }
    // Einheiten zeichnen
    for (Entity *entity: entities) {
        entity->render();
    }

    terrainManager->render();
}

/**
 * Speicher frei geben
 */
Game::~Game() {
    delete skyboxEntity;
    delete playerEntity;
    delete terrainEntity;

    for (StaticEntity *entity: medicCases) {
        delete entity;
    }

    for (StaticEntity *entity: magazineCases) {
        delete entity;
    }

    for (EnemyEntity *entity: enemies) {
        delete entity;
    }

    delete terrainManager;
    delete lightManager;

    delete terrainModel;
    delete gunModel;
    delete ghostModel;
    delete skyboxModel;
    delete magazineCaseModel;
    delete medicCaseModel;

    delete uboMatrices;
};
