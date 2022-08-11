//
// Created by Patrick on 04.08.2022.
//

#include "Entity.h"

Entity::Entity(Model *model) : model(model) {
    this->position = Vector3f();
    this->scaling = 1.0;
    this->rotationX = 0;
    this->rotationY = 0;
    this->rotationZ = 0;
}

void Entity::setPosition(float x, float y, float z) {
    this->position = Vector3f(x, y, z);
}

void Entity::setRotationX(float newRotationX) {
    this->rotationX = newRotationX;
}

void Entity::setRotationY(float newRotationY) {
    this->rotationY = newRotationY;
}

void Entity::setRotationZ(float newRotationZ) {
    this->rotationZ = newRotationZ;
}

void Entity::setScaling(float newScaling) {
    this->scaling = newScaling;
}

void Entity::update(float deltaTime) {
    this->model->update(deltaTime);
}

void Entity::render(const Camera &camera) {
    this->model->translate(position);
    this->model->rotateX(rotationX);
    this->model->rotateY(rotationY);
    this->model->rotateZ(rotationZ);
    this->model->scale(scaling);
    this->model->render(camera);
}

Entity::~Entity() = default;
