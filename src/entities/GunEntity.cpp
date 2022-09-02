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

    readyToFire = true;

    reloading = false;
    reloadTime = 1.25f;
    reloadTimer = 0;

    maxAmmo = 30;
    ammo = maxAmmo;
    magazines = 5;
}

GunEntity::~GunEntity() = default;

void GunEntity::update(float deltaTime) {
    if (reloading) {
        SoundManager::getInstance().play2DSound("../assets/Sounds/reload.mp3", false, true);
        GUIManager::getInstance().updateSpinner(25.0f, 7.5f, 5.0f);
        GUIManager::getInstance().drawInfo("Reloading", 1.0f);
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

void GunEntity::render() {
    this->model->shader->setTransform(transformation);
    this->model->render();

    if (!reloading) {
        GUIManager::getInstance().drawCrosshair(2.0f, 10.0f, Color(1.0f, 1.0f, 1.0f, 1.0f), ammo == 0);
    }
}

void GunEntity::reload() {
    if (ammo < maxAmmo && !reloading && magazines > 0) {
        this->reloading = true;
        magazines--;
    }
}

bool GunEntity::startShoot() {
    if (!readyToFire || ammo == 0 || reloading) {
        SoundManager::getInstance().play2DSound("../assets/Sounds/gun-dry-firing-7-39792.mp3");
        return false;
    }

    SoundManager::getInstance().play2DSound("../assets/Sounds/gunshot.mp3");
    ammo--;
    readyToFire = false;
    return true;
}

void GunEntity::endShoot() {
    readyToFire = true;
}

void GunEntity::addMagazines(unsigned int count) {
    this->magazines += count;
}

void GunEntity::setAmmo(unsigned int count) {
    this->ammo = count;
}

void GunEntity::setMagazines(unsigned int count) {
    this->magazines = count;
}

AABB GunEntity::getTransformedBoundingBox() const {
    return this->model->getBoundingBox().transform(transformation);
}


