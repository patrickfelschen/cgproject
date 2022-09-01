#include "EnemyEntity.h"
#include "../maths/Random.h"
#include "TerrainEntity.h"
#include <algorithm>

#define TO_RAD(deg) (deg * std::numbers::pi / 180.0)
#define TO_DEG(rad) (rad * 180.0 / std::numbers::pi)

EnemyEntity::EnemyEntity(const ObjectModel *model, const TerrainEntity *terrainEntity) : Entity() {
    this->model = model;
    this->terrainEntity = terrainEntity;
    this->maxLife = 1;
    this->life = maxLife;
    this->speed = Random::randFloat(1, 2);
    setScaling(0.2f);
    this->sound = SoundManager::getInstance().play3DSound("../assets/Sounds/ghost.mp3", this->position, true,true);
    this->sound->setIsPaused(false);
    this->sound->setVolume(0.0f);
}

EnemyEntity::~EnemyEntity() {
    this->sound ->drop();
}

void EnemyEntity::respawn() {
    this->life = maxLife;
    Vector3f newPos = terrainEntity->getRandomPosition(Vector3f(0, 1.2f, 0));
    setPosition(newPos);
}

void EnemyEntity::update(float deltaTime) {
    // Objekt zum Spieler drehen
    Vector3f dirToTarget = (targetPosition - position).normalize();
    float pitch = asin(-dirToTarget.y);
    float yaw = atan2(dirToTarget.x, dirToTarget.z);
    yaw = TO_DEG(yaw) + yawOffset;
    pitch = TO_DEG(pitch) + pitchOffset;
    setRotation(Vector3f(0.0f, yaw, pitch));
    // Objekt bewegen und auf Terrainoberfläche halten
    setPositionVelocity(dirToTarget * speed);
    float height = terrainEntity->getHeightOfPosition(this->getPosition());
    if (this->getPosition().y <= (height + groundOffset)) {
        this->setPosition(Vector3f(this->getPosition().x, height + groundOffset, this->getPosition().z));
    }
    sound->setPosition(irrklang::vec3df(this->position.x, this->position.y, this->position.z));
    Entity::update(deltaTime);
}

void EnemyEntity::render() {
    this->model->shader->setTransform(transformation);
    this->model->render();
}

AABB EnemyEntity::getTransformedBoundingBox() const {
    return this->model->getBoundingBox().transform(transformation);
}

void EnemyEntity::setTargetPosition(const Vector3f &targetPosition) {
    this->targetPosition = targetPosition;
}

void EnemyEntity::setSpeed(float speed) {
    this->speed = speed;
}

bool EnemyEntity::isDead() const {
    return life <= 0;
}

void EnemyEntity::decreaseLife(unsigned int value) {
    if(life <= 0) return;
    life -= value;
}
