//
// Created by Patrick on 04.08.2022.
//

#include "Entity.h"
#define TO_RAD(deg) (deg * std::numbers::pi / 180.0)

Entity::Entity() {
    this->position = Vector3f();
    this->scaleFactor = 1.0;
    this->rotAngleX = 0;
    this->rotAngleY = 0;
    this->rotAngleZ = 0;
}

void Entity::setPosition(float x, float y, float z) {
    this->position = Vector3f(x, y, z);
}

void Entity::setPosition(const Vector3f &pos) {
    this->position = pos;
}

void Entity::setRotationX(float newRotationX) {
    this->rotAngleX = newRotationX;
}

void Entity::setRotationY(float newRotationY) {
    this->rotAngleY = newRotationY;
}

void Entity::setRotationZ(float newRotationZ) {
    this->rotAngleZ = newRotationZ;
}

void Entity::setScaling(float newScaling) {
    this->scaleFactor = newScaling;
}

void Entity::update(float deltaTime) {
    Matrix translation, rotationX, rotationY, rotationZ, scaling;

    translation.translation(this->position);
    rotationX.rotationX(TO_RAD(this->rotAngleX));
    rotationY.rotationY(TO_RAD(this->rotAngleY));
    rotationZ.rotationZ(TO_RAD(this->rotAngleZ));
    scaling.scale(this->scaleFactor);

    this->transformation = translation * rotationX * rotationY * rotationZ * scaling;
}

const Vector3f &Entity::getPosition() const {
    return position;
}

float Entity::getRotAngleX() const {
    return rotAngleX;
}

float Entity::getRotAngleY() const {
    return rotAngleY;
}

float Entity::getRotAngleZ() const {
    return rotAngleZ;
}

float Entity::getScaleFactor() const {
    return scaleFactor;
}

Entity::~Entity() = default;
