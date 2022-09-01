//
// Created by Patrick on 30.08.2022.
//

#include <cassert>
#include "LightManager.h"

#define TO_RAD(deg) (deg * std::numbers::pi / 180.0)

LightManager::LightManager(const Camera *camera) : camera(camera) {
    this->uboSpotLights = new UniformBuffer(sizeof(Lights), 1);

    // SPOTS
    // addSpot(Vector3f(0, 2, 0), down);

    // DIRS
    addDir(Vector3f(0, -1, 0));

    // POINTS
    // addPoint(Vector3f(0, 3, 0));
}

LightManager::~LightManager() {
    delete uboSpotLights;
}

void LightManager::render() {
    setDynamicLight(camera->getPosition(), camera->getDirection());
    this->uboSpotLights->setSubData(offsetof(Lights, dynamicLight), sizeof(Light), &lights.dynamicLight);
}

void LightManager::setDynamicLight(Vector3f position, Vector3f direction) {
    Light l;
    l.type = SPOT;

    l.position = position;
    l.direction = direction;

    l.ambient = Color(0.0f, 0.0f, 0.0f);
    l.diffuse = Color(1.0f, 1.0f, 1.0f);
    l.specular = Color(1.0f, 1.0f, 1.0f);

    l.constant = 1.0f;
    l.linear = 0.09f;
    l.quadratic = 0.032f;

    l.cutOff = static_cast<float>(cos(TO_RAD(12.5f)));
    l.outerCutOff = static_cast<float>(cos(TO_RAD(20.0f)));

    this->lights.dynamicLight = l;
}

void LightManager::addPoint(Vector3f position) {
    Light l;
    l.type = POINT;

    l.position = position;

    l.ambient = Color(0.05f, 0.05f, 0.05f);
    l.diffuse = Color(0.8f, 0.8f, 0.1f);
    l.specular = Color(0.7f, 0.7f, 0.1f);

    l.constant = 1.0f;
    l.linear = 0.35f;
    l.quadratic = 0.44f;

    this->lights.staticLights[lights.staticLightsCount++] = l;
    this->uboSpotLights->setSubData(0, sizeof(Lights), &lights);
}

void LightManager::addSpot(Vector3f position, Vector3f direction) {
    Light l;
    l.type = SPOT;

    l.position = position;
    l.direction = direction;

    l.ambient = Color(0.0f, 0.0f, 0.0f);
    l.diffuse = Color(1.0f, 1.0f, 1.0f);
    l.specular = Color(1.0f, 1.0f, 1.0f);

    l.constant = 1.0f;
    l.linear = 0.09f;
    l.quadratic = 0.032f;

    l.cutOff = static_cast<float>(cos(TO_RAD(12.5f)));
    l.outerCutOff = static_cast<float>(cos(TO_RAD(20.0f)));

    this->lights.staticLights[lights.staticLightsCount++] = l;
    this->uboSpotLights->setSubData(0, sizeof(Lights), &lights);
}

void LightManager::addDir(Vector3f dir) {
    Light l;
    l.type = DIR;

    l.direction = dir;

    l.ambient = Color(0.010f, 0.010f, 0.010f);
    l.diffuse = Color(0.010f, 0.010f, 0.010f);
    l.specular = Color(0.005f, 0.005f, 0.005f);

    this->lights.staticLights[lights.staticLightsCount++] = l;
    this->uboSpotLights->setSubData(0, sizeof(Lights), &lights);
}




