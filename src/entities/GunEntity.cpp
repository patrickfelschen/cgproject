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
        GUIManager::getInstance().updateSpinner(25.0f, 7.5f, 5.0f);
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
    this->model->shader->setTransform(transformation);
    this->model->render();

    if(!reloading) {
        GUIManager::getInstance().drawCrosshair(2.0f, 10.0f, Color(1.0f, 1.0f, 1.0f, 1.0f), ammo == 0);
    }
}

void GunEntity::reload() {
    if (ammo < maxAmmo && !reloading && magazines > 0) {
        this->reloading = true;
        magazines--;
    }
}

void GunEntity::startShoot(const Camera &camera) {
    if (!readyToFire || ammo == 0 || reloading) return;

    SoundManager::getInstance().play2DSound("../assets/Sounds/gunshot.mp3");
    ammo--;
    Ray ray;
    ray.origin = camera.getPosition();
    ray.direction = camera.getDirection() * range;
    std::sort(targets.begin(), targets.end(), sortPosAsc());
    for (auto & target : targets) {
        bool intersection = target->getTransformedBoundingBox().intersection(ray);
        if (intersection) {
            target->hit = true;
            break;
        }
        //printf("Element: %i - Distance: %f\n", i, targets.at(i)->getDistanceToPlayer());
    }
    readyToFire = false;

}

void GunEntity::endShoot() {
    readyToFire = true;
}

void GunEntity::setTargets(const std::vector<EnemyEntity *> &v) {
    targets = v;
}

void GunEntity::addMagazines(unsigned int count) {
    this->magazines += count;
}

void GunEntity::setAmmo(unsigned int ammo) {
    GunEntity::ammo = ammo;
}

void GunEntity::setMagazines(unsigned int magazines) {
    GunEntity::magazines = magazines;
}


