
#include "EnemyEntity.h"

#define TO_RAD(deg) (deg * std::numbers::pi / 180.0)
#define TO_DEG(rad) (rad * 180.0 / std::numbers::pi)

/**
 * Initialisiert Entitiy Werte
 * 3D Sound wird gestartet (startPaused = true, damit Pointer zurückgegeben wird) und verstummt
 * @param model Zur Entity gehöriges 3D Modell
 * @param terrainEntity Entitiy des Terrains
 */
EnemyEntity::EnemyEntity(const ObjectModel *model, const TerrainEntity *terrainEntity) : Entity() {
    this->model = model;
    this->terrainEntity = terrainEntity;
    this->maxLife = 1;
    this->life = maxLife;
    this->speed = Random::randFloat(1, 2);

    this->sound = SoundManager::getInstance().play3DSound("../assets/Sounds/ghost.mp3", this->position, true, true);
    this->sound->setIsPaused(false);
    this->sound->setVolume(0.0f);
}

EnemyEntity::~EnemyEntity() {
    this->sound->drop();
}

/**
 * Setzt das aktuelle Leben der Entitiy auf das maximale Leben
 * Setzt Entitiy auf eine zufällige Position
 */
void EnemyEntity::respawn() {
    this->life = maxLife;
    Vector3f newPos = terrainEntity->getRandomPosition(Vector3f(0, 1.2f, 0));
    setPosition(newPos);
}

/**
 * Berechnet Ausrichtung zum Spieler, prüft Höhe auf dem Terrain und verschiebt die Position des 3D-Sounds
 * @param deltaTime Zeitunterschied zum letzten Frame
 */
void EnemyEntity::update(float deltaTime) {
    // Vektor von Entity zu Spieler
    Vector3f dirToTarget = (targetPosition - position).normalize();
    // Aus dirToTarget Rotation der Entitiy berechnen
    // https://stackoverflow.com/questions/2782647/how-to-get-yaw-pitch-and-roll-from-a-3d-vector
    // https://stackoverflow.com/questions/283406/what-is-the-difference-between-atan-and-atan2-in-c
    float pitch = asin(-dirToTarget.y);
    float yaw = atan2(dirToTarget.x, dirToTarget.z);
    yaw = TO_DEG(yaw) + yawOffset;
    pitch = TO_DEG(pitch) + pitchOffset;
    setRotation(Vector3f(0.0f, yaw, pitch));
    // Objekt bewegen und auf Terrainoberfläche halten
    setPositionVelocity(dirToTarget * speed);
    bool onTerrain;
    float height = terrainEntity->getHeightOfPosition(this->getPosition(), onTerrain);
    if (onTerrain && this->getPosition().y <= (height + groundOffset)) {
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

void EnemyEntity::increaseSpeed(float value) {
    this->speed += value;
}

bool EnemyEntity::isDead() const {
    return life <= 0;
}

void EnemyEntity::decreaseLife(unsigned int value) {
    if (life <= 0) return;
    life -= value;
}

void EnemyEntity::increaseMaxLife(unsigned int value) {
    maxLife += value;
}

irrklang::ISound *EnemyEntity::getSound() const {
    return sound;
}

unsigned int EnemyEntity::getLife() const {
    return life;
}

unsigned int EnemyEntity::getMaxLife() const {
    return maxLife;
}

void EnemyEntity::setSpeed(float speed) {
    EnemyEntity::speed = speed;
}

void EnemyEntity::setMaxLife(unsigned int maxLife) {
    EnemyEntity::maxLife = maxLife;
}
