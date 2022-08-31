#include "EnemyEntity.h"
#include "../maths/Random.h"

#define TO_RAD(deg) (deg * std::numbers::pi / 180.0)
#define TO_DEG(rad) (rad * 180.0 / std::numbers::pi)

EnemyEntity::EnemyEntity(const ObjectModel* model) : Entity() {
    this->model = model;
    this->hit = false;
    this->speed = Random::randFloat(1, 2);
    setScaling(0.2f);
}

EnemyEntity::~EnemyEntity() = default;

void EnemyEntity::respawn(const Vector3f &pos) {
    this->hit = false;
    setPosition(pos);
    speed = Random::randFloat(1, 2);
}

float yawOffset = 90;
float pitchOffset = 20;
void EnemyEntity::update(float deltaTime) {
    Vector3f dirToTarget = (targetPosition - position).normalize();

    float pitch = asin(-dirToTarget.y);
    float yaw = atan2(dirToTarget.x, dirToTarget.z);

    yaw = TO_DEG(yaw) + yawOffset;
    pitch = TO_DEG(pitch) + pitchOffset;

//  Vector3f nextPos = dirToTarget speed + Vector3f(0.0f, (gravity * deltaTime) * 3, 0.0f);

    setRotation(Vector3f(0.0f, yaw, pitch));
    setPositionVelocity(dirToTarget * speed);
    setDistanceToPlayer(position.distanceTo(targetPosition));
    Entity::update(deltaTime);
}

void EnemyEntity::render(const Camera &camera) {
    this->model->shader->setTransform(transformation);
    this->model->render();
}

float EnemyEntity::getDistanceToPlayer() const {
    return distanceToPlayer;
}

void EnemyEntity::setDistanceToPlayer(float distance) {
    EnemyEntity::distanceToPlayer = distance;
}

AABB EnemyEntity::getTransformedBoundingBox() const {
    return this->model->getBoundingBox().transform(transformation);
}

void EnemyEntity::setTargetPosition(const Vector3f &targetPosition) {
    this->targetPosition = targetPosition;
}