//
// Created by Patrick on 11.08.2022.
//

#include "GunEntity.h"


#define TO_RAD(deg) (deg * std::numbers::pi / 180.0)
#define TO_DEG(rad) (rad * 180.0 / std::numbers::pi)

GunEntity::GunEntity(ObjectModel *model) : Entity() {
    this->model = model;

    setScaling(0.025);
    setPosition(Vector3f(0.026, -0.015, -0.045));
    setRotation(Vector3f(0, -95, 0));
}

GunEntity::~GunEntity() = default;

void GunEntity::update(float deltaTime) {
    if (reloading) {
        reloadTimer += deltaTime;
        if (reloadTimer >= reloadTime) {
            reloadTimer = 0;
            reloading = false;
            ammo = maxAmmo;
        }
    }

    GUIManager::getInstance().updateAmmoWindow(ammo, magazines);
    Entity::update(deltaTime);
}

void GunEntity::render(const Camera &camera) {
    this->model->shader->setCameraPosition(camera.getPosition());
    this->model->shader->setProjection(camera.getProj());
    //this->model->shader->setView(camera.getView());
    this->model->shader->setTransform(transformation);
    this->model->render();
}

void GunEntity::reload() {
    if (ammo < maxAmmo && !reloading && (magazines > 0)) {
        this->reloading = true;
        magazines--;
    }
}

void GunEntity::startShoot(const Camera &camera) {
    if (!readyToFire || ammo == 0 || reloading) return;

    ammo--;
    Ray ray;
    ray.origin = camera.getPosition();
    ray.direction = camera.getDirection() * range;
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

void GunEntity::endShoot() {
    readyToFire = true;
}

void GunEntity::setTargets(const std::vector<CoinEntity *> &v) {
    targets = v;
}


