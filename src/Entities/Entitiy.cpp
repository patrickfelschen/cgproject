#include "Entitiy.hpp"

Entity::Entity() {
}

Entity::Entity(TexturedModel *model, Vector3f position, float rotX, float rotY, float rotZ, float scale) {
    this->model = model;
    this->position = position;
    this->rotX = rotX;
    this->rotY = rotY;
    this->rotZ = rotZ;
    this->scale = scale;
}

Entity::~Entity() {
}

TexturedModel *Entity::getModel() {
    return this->model;
}

Vector3f Entity::getPosition() {
    return this->position;
}

float Entity::getRotX() const {
    return this->rotX;
}

float Entity::getRotY() const {
    return this->rotY;
}

float Entity::getRotZ() const {
    return this->rotZ;
}

float Entity::getScale() const {
    return this->scale;
}

void Entity::setModel(TexturedModel *model) {
    this->model = model;
}

void Entity::setPosition(Vector3f pos) {
    this->position = pos;
}

void Entity::setRotX(float rotX) {
    this->rotX = rotX;
}

void Entity::setRotY(float rotY) {
    this->rotY = rotY;
}

void Entity::setRotZ(float rotZ) {
    this->rotZ = rotZ;
}

void Entity::setScale(float scale) {
    this->scale = scale;
}

void Entity::increasePosition(float dx, float dy, float dz) {
    this->position.X += dx;
    this->position.Y += dy;
    this->position.Z += dz;

}

void Entity::increaseRotation(float dx, float dy, float dz) {
    this->rotX += dx;
    this->rotY += dy;
    this->rotZ += dz;
}


