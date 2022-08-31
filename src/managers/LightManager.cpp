//
// Created by Patrick on 30.08.2022.
//

#include <cassert>
#include "LightManager.h"

#define TO_RAD(deg) (deg * std::numbers::pi / 180.0)

LightManager::LightManager(const Camera *camera) : camera(camera) {
    // SPOTS
    //addSpot(Vector3f(0, 2, 0), down);

    // DIRS
    //addDir(down);

    // POINTS
    addPoint(Vector3f(0, 10, 0));

    this->uboSpotLights = new UniformBuffer(sizeof(Lights), 1);
    this->uboSpotLights->setSubData(0, sizeof(Lights), &lights);
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
    l.outerCutOff = static_cast<float>(cos(TO_RAD(15.0f)));

    this->lights.dynamicLight = l;
}

void LightManager::addPoint(Vector3f position) {
    Light l;
    l.type = POINT;

    l.position = position;

    l.ambient = Color(0.05f, 0.05f, 0.05f);
    l.diffuse = Color(0.8f, 0.8f, 0.8f);
    l.specular = Color(0.6f, 0.6f, 0.6f);

    l.constant = 1.0f;
    l.linear = 0.09f;
    l.quadratic = 0.032f;

    this->lights.staticLights[lights.staticLightsCount++] = l;
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
    l.outerCutOff = static_cast<float>(cos(TO_RAD(15.0f)));

    this->lights.staticLights[lights.staticLightsCount++] = l;
}

void LightManager::addDir(Vector3f dir) {
    Light l;
    l.type = DIR;

    l.direction = dir;

    l.ambient = Color(0.05f, 0.05f, 0.05f);
    l.diffuse = Color(0.4f, 0.4f, 0.4f);
    l.specular = Color(0.5f, 0.5f, 0.5f);

    this->lights.staticLights[lights.staticLightsCount++] = l;
}




