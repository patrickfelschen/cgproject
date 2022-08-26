//
// Created by Patrick on 04.08.2022.
//

#include "Entity.h"

#define TO_RAD(deg) (deg * std::numbers::pi / 180.0)

Entity::Entity() {
    this->position = Vector3f();
    this->positionOffset = Vector3f();
    this->positionVelocity = Vector3f();
    this->rotation = Vector3f();
    this->rotationVelocity = Vector3f();
    this->scaleFactor = 1.0;
    this->transformation.identity();
}

void Entity::setPosition(const Vector3f &pos) {
    this->position = pos;
}

void Entity::setRotation(const Vector3f rot) {
    this->rotation = rot;
}

void Entity::setScaling(float newScaling) {
    this->scaleFactor = newScaling;
}

void Entity::setPositionVelocity(const Vector3f &positionVelocity) {
    this->positionVelocity = positionVelocity;
}

void Entity::setRotationVelocity(const Vector3f &rotationVelocity) {
    this->rotationVelocity = rotationVelocity;
}

void Entity::update(float deltaTime) {
    this->position += positionVelocity * deltaTime;
    this->rotation += rotationVelocity * deltaTime;

    Matrix translation, rotationX, rotationY, rotationZ, scaling;

    translation.translation(this->position + this->positionOffset);
    rotationX.rotationX(TO_RAD(this->rotation.x));
    rotationY.rotationY(TO_RAD(this->rotation.y));
    rotationZ.rotationZ(TO_RAD(this->rotation.z));
    scaling.scale(this->scaleFactor);

    this->transformation = translation * rotationX * rotationY * rotationZ * scaling;
}

const Vector3f &Entity::getPosition() const {
    return position;
}

Entity::~Entity() = default;
