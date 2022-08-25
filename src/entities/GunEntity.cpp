//
// Created by Patrick on 11.08.2022.
//

#include "GunEntity.h"


#define TO_RAD(deg) (deg * std::numbers::pi / 180.0)
#define TO_DEG(rad) (rad * 180.0 / std::numbers::pi)

GunEntity::GunEntity(ObjectModel *model, GLFWwindow &window) : Entity(), window(window) {
    this->model = model;

    setScaling(0.025);
    setPosition(Vector3f(0.026, -0.015, -0.045));
    setRotation(Vector3f(0, -95, 0));
}

GunEntity::~GunEntity() = default;

void GunEntity::update(float deltaTime) {
//    printf("Targets: %i\n", targets->size());
    GUIManager::getInstance().updateAmmoWindow(ammo);
    Entity::update(deltaTime);
}

void GunEntity::render(const Camera &camera) {
    if (glfwGetMouseButton(&window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        shoot(camera);
    }
    if (glfwGetMouseButton(&window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
        readyToFire = true;
    }

    this->model->shader->setCameraPosition(camera.getPosition());
    this->model->shader->setProjection(camera.getProj());
    //this->model->shader->setView(camera.getView());
    this->model->shader->setTransform(transformation);
    this->model->render();
}

void GunEntity::shoot(const Camera &camera) {
    if (readyToFire) {
        ammo--;
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


