#include "CoinEntity.h"

CoinEntity::CoinEntity(const Model *model) : Entity(model) {
    setScaling(0.05f);
    respawn(Vector3f());
}

CoinEntity::~CoinEntity() = default;

void CoinEntity::respawn(const Vector3f &pos) {
    float range = 5.0f;
    this->hit = false;

    float x = rndFloat(pos.x - range, pos.x + range);
    float y = rndFloat(pos.y, pos.y);
    float z = rndFloat(pos.z - range, pos.z + range);

    setPosition(x, y, z);
    speed = rndFloat(2, 10);
}

void CoinEntity::update(float deltaTime) {
    rotation += deltaTime * 100;
    setRotationY(rotation);
    Entity::update(deltaTime);
}

void CoinEntity::render(const Camera &camera) {
    Vector3f dirToPlayer = (camera.getPosition() - position).normalize() *= (speed / 1000);
    position += dirToPlayer;
    setPosition(position);
    setDistanceToPlayer(position.distanceTo(camera.getPosition()));
    Entity::render(camera);
}

float CoinEntity::rndFloat(float min, float max) {
    return ((float(rand()) / float(RAND_MAX)) * (max - min)) + min;
}

float CoinEntity::getDistanceToPlayer() const {
    return distanceToPlayer;
}

void CoinEntity::setDistanceToPlayer(float distance) {
    CoinEntity::distanceToPlayer = distance;
}