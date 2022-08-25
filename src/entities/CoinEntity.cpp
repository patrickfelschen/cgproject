#include "CoinEntity.h"
#include "../maths/Random.h"

CoinEntity::CoinEntity(const ObjectModel *model) : Entity() {
    this->model = model;
    this->hit = false;
    this->speed = Random::randFloat(2, 8);
    setScaling(0.10f);
}

CoinEntity::~CoinEntity() = default;

void CoinEntity::respawn(const Vector3f &pos) {
    this->hit = false;
    setPosition(pos);
    speed = Random::randFloat(2, 8);
}

void CoinEntity::update(float deltaTime) {
    Vector3f dirToTarget = (targetPosition - position).normalize();
    setPositionVelocity(dirToTarget);
    setRotationVelocity(Vector3f(0, 20, 0));

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
