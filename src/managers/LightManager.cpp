//
// Created by Patrick on 30.08.2022.
//

#include <cassert>
#include "LightManager.h"

#define TO_RAD(deg) (deg * std::numbers::pi / 180.0)

/**
 * Initialisiert einen UniformBuffer für die Lichter und fügt eine globale Beleuchtun hinzu
 * @param camera Kamera um dynamische Beleuchtung anhand der Kamera Richtung und Position zu ermöglichen
 */
LightManager::LightManager(const Camera *camera) : camera(camera) {
    this->uboSpotLights = new UniformBuffer(sizeof(Lights), 1);

    // STATIC SPOTS
    // addSpot(...);

    // STATIC DIRS
    addDir(Vector3f(0, -1, 0));

    // STATIC POINTS
    // addPoint(...);
}

LightManager::~LightManager() {
    delete uboSpotLights;
}

/**
 * Aktualisiert dynamisches Spotlight im UniformBuffer
 */
void LightManager::render() {
    setDynamicLight(camera->getPosition(), camera->getTarget());
    this->uboSpotLights->setSubData(offsetof(Lights, dynamicLight), sizeof(Light), &lights.dynamicLight);
}

/**
 * Erzeugt ein dynamisches Spotlight
 * @param position Position des Lichtes
 * @param direction Richtung des Lichtes
 */
void LightManager::setDynamicLight(Vector3f position, Vector3f direction) {
    Light l;
    l.type = SPOT;

    l.position = position;
    l.direction = direction;

    l.ambient = Color(0.0f, 0.0f, 0.0f);
    l.diffuse = Color(1.0f, 1.0f, 1.0f);
    l.specular = Color(1.0f, 1.0f, 1.0f);

    // https://learnopengl.com/Lighting/Light-casters
    // https://wiki.ogre3d.org/tiki-index.php?page=-Point+Light+Attenuation
    l.constant = 1.0f;
    l.linear = 0.09f;
    l.quadratic = 0.032f;

    l.cutOff = static_cast<float>(cos(TO_RAD(12.5f)));
    l.outerCutOff = static_cast<float>(cos(TO_RAD(20.0f)));

    this->lights.dynamicLight = l;
}

/**
 * Erzeugt ein statisches Pointlight
 * @param position Position des Spotlights
 */
void LightManager::addPoint(Vector3f position) {
    Light l;
    l.type = POINT;

    l.position = position;

    l.ambient = Color(0.05f, 0.05f, 0.05f);
    l.diffuse = Color(0.8f, 0.8f, 0.3f);
    l.specular = Color(0.7f, 0.7f, 0.3f);

    // https://learnopengl.com/Lighting/Light-casters
    // https://wiki.ogre3d.org/tiki-index.php?page=-Point+Light+Attenuation
    l.constant = 1.0f;
    l.linear = 0.09f;
    l.quadratic = 0.032f;

    // Licht zu staticLights hinzufügen und in UniformBuffer setzen
    this->lights.staticLights[lights.staticLightsCount++] = l;
    this->uboSpotLights->setSubData(0, sizeof(Lights), &lights);
}

/**
 * Erzeugt ein statisches Spotlight
 * @param position Position des Spotlights
 * @param direction Richtung des Spotlights
 */
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

/**
 * Fügt ein statisches Directionallight hinzu
 * @param dir Richtung des Lichtes
 */
void LightManager::addDir(Vector3f dir) {
    Light l;
    l.type = DIR;

    l.direction = dir;

    l.ambient = Color(0.010f, 0.010f, 0.010f);
    l.diffuse = Color(0.010f, 0.010f, 0.010f);
    l.specular = Color(0.005f, 0.005f, 0.005f);

    // Licht zu staticLights hinzufügen und in UniformBuffer setzen
    this->lights.staticLights[lights.staticLightsCount++] = l;
    this->uboSpotLights->setSubData(0, sizeof(Lights), &lights);
}




