//
// Created by Patrick on 11.08.2022.
//

#include "GunEntity.h"

#define TO_RAD(deg) (deg * std::numbers::pi / 180.0)
#define TO_DEG(rad) (rad * 180.0 / std::numbers::pi)

GunEntity::GunEntity(Model *model, GLFWwindow &window) : Entity(model), window(window) {
    weaponOffset = Vector3f(0.026, -0.015, -0.045);
    setScaling(0.025);

}

GunEntity::~GunEntity() {

}

void GunEntity::update(float deltaTime) {
//    printf("Targets: %i\n", targets->size());
    Entity::update(deltaTime);
}

void GunEntity::render(const Camera &camera) {
    if(glfwGetMouseButton(&window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        shoot(camera);
    }
    if(glfwGetMouseButton(&window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
        readyToFire = true;
    }

    setPosition(weaponOffset);
    setRotationY(TO_RAD(-95));

    Entity::render(camera);
}

void GunEntity::shoot(const Camera &camera) {
    if(readyToFire) {
        Ray ray;

        ray.origin = camera.getPosition();
        ray.direction = camera.getDirection() * 3;


        for(unsigned int i = 0; i < targets->size(); i++) {
            bool intersection = targets->at(i)->getTransformedBoundingBox().intersection(ray);
            if(intersection) {
                printf("hit\n");
                targets->erase(targets->begin() + i);
                break;
            }
        }

        readyToFire = false;
    }
}

void GunEntity::setTargets(std::vector<Entity *> *v) {
    targets = v;
}


