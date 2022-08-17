//
// Created by Patrick on 11.08.2022.
//

#include "GunEntity.h"


#define TO_RAD(deg) (deg * std::numbers::pi / 180.0)
#define TO_DEG(rad) (rad * 180.0 / std::numbers::pi)

GunEntity::GunEntity(Model *model) : Entity(model) {
    setScaling(0.025);
}

GunEntity::~GunEntity() {

}

void GunEntity::update(float deltaTime) {
    Entity::update(deltaTime);
}

void GunEntity::render(const Camera &camera) {

    setPosition(Vector3f(0.026, -0.015, -0.045));
    setRotationY(TO_RAD(-95));

    Entity::render(camera);
}




