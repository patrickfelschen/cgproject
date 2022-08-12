//
// Created by Patrick on 11.08.2022.
//

#include "GunEntity.h"

GunEntity::GunEntity(Model *model) : Entity(model) {
    setScaling(0.005);
}

GunEntity::~GunEntity() {

}

void GunEntity::update(float deltaTime) {
    Entity::update(deltaTime);
}

void GunEntity::render(const Camera &camera) {
    Vector3f gunPos = camera.getPosition();

    this->setPosition(gunPos.x, gunPos.y, gunPos.z);

    Entity::render(camera);
}




