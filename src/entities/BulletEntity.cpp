#include "BulletEntity.h"

BulletEntity::BulletEntity(Model *model, Vector3f startPos, Vector3f dir) : Entity(model), pos(startPos), dir(dir) {
    pos += Vector3f(0.0f, -0.5f, 0.0f);
    setScaling(0.01f);
}

BulletEntity::~BulletEntity() {

}

void BulletEntity::setYaw(float yaw) {
    BulletEntity::yaw = yaw;
}

void BulletEntity::setPitch(float pitch) {
    BulletEntity::pitch = pitch;
}

void BulletEntity::update(float deltaTime) {
    Entity::update(deltaTime);
}

void BulletEntity::render(const Camera &camera) {
    pos += dir * 0.05f;
    setPosition(pos);
    setRotationY(-yaw);
    setRotationZ(pitch);

    Entity::render(camera);
}

