#include "CoinEntity.h"

CoinEntity::CoinEntity(const ObjectModel *model) : Entity() {
    this->model = model;
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

    setPosition(Vector3f(x, y, z));
    speed = rndFloat(2, 4);
}

void CoinEntity::update(float deltaTime) {
    Vector3f dirToTarget = (targetPosition - position).normalize();
    setRotationVelocity(Vector3f(0.0f, 100.0f, 0.0f));
    setPositionVelocity(dirToTarget);

    setDistanceToPlayer(position.distanceTo(targetPosition));

    Entity::update(deltaTime);
}

void CoinEntity::render(const Camera &camera) {
    this->model->shader->setCameraPosition(camera.getPosition());
    this->model->shader->setProjection(camera.getProj());
    this->model->shader->setView(camera.getView());
    this->model->shader->setTransform(transformation);

    this->model->render();
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

AABB CoinEntity::getTransformedBoundingBox() const {
    return this->model->getBoundingBox().transform(transformation);
}

void CoinEntity::setTargetPosition(const Vector3f &targetPosition) {
    this->targetPosition = targetPosition;
}
