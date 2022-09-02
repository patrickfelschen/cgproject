//
// Created by Patrick on 01.09.2022.
//

#include "PlayerEntity.h"

PlayerEntity::PlayerEntity(Camera *camera, TerrainEntity *terrainEntity) : Entity() {
    this->terrainEntity = terrainEntity;
    this->camera = camera;
    this->hitCount = 0;
    this->maxLife = 5;
    this->life = maxLife;
    this->particleManager = new ParticleManager(400);
}

PlayerEntity::~PlayerEntity() {
    delete gunEntity;
    delete particleManager;
}

void PlayerEntity::init() {
    this->hitCount = 0;
    this->life = maxLife;
    this->gunEntity->setAmmo(30);
    this->gunEntity->setMagazines(5);
}

void PlayerEntity::startShoot() {
    if (this->gunEntity->startShoot()) {
        // Schussreichweite
        float gunRange = 200.0f;
        // Strahl in Kamerarichtung
        Ray ray(camera->getPosition(), camera->getTarget());
        EnemyEntity *hitEnemy = getFirstIntersection(ray, gunRange);
        // Gegner Leben abziehen
        if (hitEnemy != nullptr) {
            hitEnemy->decreaseLife(1);
        }
    }
}

void PlayerEntity::update(float deltaTime) {
    // Prüfen ob Spieler im Terrain Bereich ist
    terrainEntity->getHeightOfPosition(
            camera->getPosition(),
            onTerrain
    );
    // Wenn Spieler außerhalb des Terrains, Leben abziehen
    if (!onTerrain) {
        GUIManager::getInstance().drawInfo("Geh zurück!", Color(1.0f, 0, 0));
        terrainDamageTimer += deltaTime;
        if (terrainDamageTimer >= terrainDamageTime) {
            decreaseLife(1);
            terrainDamageTimer = 0;
        }
    }

    this->setPosition(camera->getPosition());
    this->gunEntity->update(deltaTime);

    Ray camRay = Ray(camera->getPosition(), camera->getTarget());

    // Prüfen ob Spieler Medic Kisten öffnen möchte
    for (StaticEntity *medicCase: this->medicCases) {
        if (checkEntityRayCollision(medicCase, camRay, 4.0f)) {
            GUIManager::getInstance().drawInfo("+1 Leben");
        }
        if (checkEntityRayCollision(medicCase, camRay, 2.0f)) {
            particleManager->spawn(medicCase->getPosition(), Color(0.0f, 1.0f, 0.0f, 1.0f));
            medicCase->respawn();
            increaseLife(1);
        }
        medicCase->update(deltaTime);
    }
    // Prüfen ob Spieler Magazine Kisten öffnen möchte
    for (StaticEntity *magazineCase: this->magazineCases) {
        if (checkEntityRayCollision(magazineCase, camRay, 4.0f)) {
            GUIManager::getInstance().drawInfo("+2 Magazine");
        }
        if (checkEntityRayCollision(magazineCase, camRay, 2.0f)) {
            particleManager->spawn(magazineCase->getPosition(), Color(0.0f, 0.0f, 1.0f, 1.0f));
            magazineCase->respawn();
            increaseMagazines(2);
        }
        magazineCase->update(deltaTime);
    }
    // Prüfen ob Spieler Gegner trifft oder vom Gegner getroffen wird
    for (EnemyEntity *enemy: enemies) {
        // Lebensbalken
        EnemyEntity *targetedEnemy = getFirstIntersection(camRay, 10.0f);
        if (targetedEnemy != nullptr) {
            GUIManager::getInstance().updateLifeWindow("enemylife", targetedEnemy->getLife(), targetedEnemy->getMaxLife(), Vector2f(GUIManager::getInstance().SCR_WIDTH / 2, 25.0f), 200, 10);
        }

        // Gegner erledigt
        if (enemy->isDead()) {
            if((hitCount % 5) == 0) {
                enemy->increaseMaxLife(1);
                increaseDifficulty();
            }
            hitCount++;
            SoundManager::getInstance().play2DSound("../assets/Sounds/fist-punch-or-kick-7171.mp3");
            particleManager->spawn(enemy->getPosition(), Color(1.0f));
            enemy->respawn();
        }
        // Spieler getroffen
        if (checkEntityPositionCollision(enemy, this, 0.4f)) {
            decreaseLife(1);
            enemy->respawn();
        }

        float distance = enemy->getPosition().distanceTo(this->position);
        if (distance < 7.0f) {
            enemy->getSound()->setVolume(std::clamp(distance, 0.0f, 1.0f));
        } else {
            enemy->getSound()->setVolume(0.0f);
        }

        enemy->setTargetPosition(camera->getPosition());
        enemy->update(deltaTime);
    }

    particleManager->update(deltaTime);
    GUIManager::getInstance().updateLifeWindow("playerLife", life, maxLife, Vector2f(160.0f, GUIManager::getInstance().SCR_HEIGHT - 50.0f));
    GUIManager::getInstance().updateScoreWindow(hitCount);
}

void PlayerEntity::render() {
    this->gunEntity->render();
    this->particleManager->render();
}

void PlayerEntity::increaseLife(unsigned int value) {
    SoundManager::getInstance().play2DSound("../assets/Sounds/heal.mp3");
    if (life == maxLife) return;
    this->life += value;
}

void PlayerEntity::decreaseLife(unsigned int value) {
    SoundManager::getInstance().play2DSound("../assets/Sounds/hit.mp3");
    SoundManager::getInstance().play2DSound("../assets/Sounds/damage.mp3");
    if (life == 0) return;
    particleManager->spawn(this->getPosition(), Color(1.0f, 0.0f, 0.0f, 1.0f));
    this->life -= value;
}

bool PlayerEntity::isAlive() const {
    return life > 0;
}

void PlayerEntity::setGunEntity(GunEntity *gunEntity) {
    this->gunEntity = gunEntity;
}

void PlayerEntity::setEnemies(const std::vector<EnemyEntity *> &enemies) {
    this->enemies = enemies;
}

void PlayerEntity::setMedicCases(const std::vector<StaticEntity *> &medicCases) {
    this->medicCases = medicCases;
}

void PlayerEntity::setMagazineCases(const std::vector<StaticEntity *> &magazineCases) {
    this->magazineCases = magazineCases;
}

bool PlayerEntity::checkEntityRayCollision(Entity *entity, const Ray &ray, float range) const {
    Ray rangeRay = Ray(ray.origin, ray.direction * range);
    return entity->getTransformedBoundingBox().intersection(rangeRay);
}

bool PlayerEntity::checkEntityPositionCollision(Entity *entity1, Entity *entity2, float offset) const {
    return entity1->getPosition().distanceTo(entity2->getPosition()) <= offset;
}

void PlayerEntity::endShoot() {
    this->gunEntity->endShoot();
}

void PlayerEntity::reload() {
    this->gunEntity->reload();
}

void PlayerEntity::increaseMagazines(unsigned int count) {
    SoundManager::getInstance().play2DSound("../assets/Sounds/magazinecase.mp3");
    this->gunEntity->addMagazines(count);
}

AABB PlayerEntity::getTransformedBoundingBox() const {
    return AABB();
}

unsigned int PlayerEntity::getHitCount() const {
    return hitCount;
}

void PlayerEntity::increaseDifficulty() {
    std::cout << "difficulty increase" << std::endl;
    for(EnemyEntity *entity: enemies) {
        entity->increaseSpeed(0.1f);
    }
}

EnemyEntity *PlayerEntity::getFirstIntersection(Ray ray, float range) {
    EnemyEntity *hitEnemy = nullptr;
    float minHitDistance = 0;
    for (EnemyEntity *enemy: enemies) {
        // Überschneidung des Rays und der Bounding Boxen prüfen
        if (checkEntityRayCollision(enemy, ray, range)) {
            // Bei mehreren Überschneidungen den nächsten Gegner wählen
            float distanceToPlayer = enemy->getPosition().distanceTo(this->getPosition());
            if (hitEnemy == nullptr || distanceToPlayer < minHitDistance) {
                hitEnemy = enemy;
                minHitDistance = distanceToPlayer;
            }
        }
    }
    return hitEnemy;
}
