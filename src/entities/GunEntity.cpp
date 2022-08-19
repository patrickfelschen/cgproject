//
// Created by Patrick on 11.08.2022.
//

#include "GunEntity.h"

#define TO_RAD(deg) (deg * std::numbers::pi / 180.0)
#define TO_DEG(rad) (rad * 180.0 / std::numbers::pi)

GunEntity::GunEntity(Model *model, GLFWwindow &window) : Entity(model), window(window) {
    setScaling(0.025);
    setPosition(0.026, -0.015, -0.045);
    setRotationY(-95);
}

GunEntity::~GunEntity() = default;

void GunEntity::update(float deltaTime) {
//    printf("Targets: %i\n", targets->size());
    Entity::update(deltaTime);
}

void GunEntity::render(const Camera &camera) {
    if (glfwGetMouseButton(&window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        shoot(camera);
    }
    if (glfwGetMouseButton(&window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
        readyToFire = true;
    }
    Entity::render(camera);
}

void GunEntity::shoot(const Camera &camera) {
    if (readyToFire) {
        Ray ray;
        ray.origin = camera.getPosition();
        ray.direction = camera.getDirection() * 3;
        std::sort(targets.begin(), targets.end(), sortPosAsc());
        for (unsigned int i = 0; i < targets.size(); i++) {
            bool intersection = targets.at(i)->getTransformedBoundingBox().intersection(ray);
            if (intersection) {
                targets.at(i)->hit = true;
                break;
            }
            printf("Element: %i - Distance: %f\n", i, targets.at(i)->getDistanceToPlayer());
        }
        readyToFire = false;
    }
}

void GunEntity::setTargets(const std::vector<CoinEntity *> &v) {
    targets = v;
}


