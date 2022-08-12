#include "CoinEntity.h"

CoinEntity::CoinEntity(Model *model) : Entity(model) {
    pos = Vector3f(
            rndFloat(-0.35, 0.95),
            rndFloat(-0.15, 0.15),
            rndFloat(-1.15, 1.15)
            );
    speed = rndFloat(2, 10);

    setPosition(pos);
    setScaling(0.05f);
}

CoinEntity::~CoinEntity() {}

void CoinEntity::update(float deltaTime) {
    rotation += deltaTime;
    setRotationY(rotation);
    Entity::update(deltaTime);
}

void CoinEntity::render(const Camera &camera) {
    Vector3f dirToPlayer = (camera.getPosition() - pos).normalize() *= (speed/1000);
    pos += dirToPlayer;
    setPosition(pos);
    Entity::render(camera);
}

float CoinEntity::rndFloat(float min, float max) {
    return ((float(rand()) / float(RAND_MAX)) * (max - min)) + min;
}