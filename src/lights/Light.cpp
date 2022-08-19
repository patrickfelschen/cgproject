//
// Created by Patrick on 17.08.2022.
//

#include "Light.h"

Light::Light() {
    this->position = Vector3f();
    this->attenuation = Vector3f(1, 0, 0);
    this->color = Color(1.0f);
}

Light::Light(const Vector3f &position, const Vector3f &attenuation, const Color &color) {
    this->position = position;
    this->attenuation = attenuation;
    this->color = color;
}

Light::~Light() = default;

const Vector3f &Light::getPosition() const {
    return position;
}

void Light::setPosition(const Vector3f &position) {
    Light::position = position;
}

const Vector3f &Light::getAttenuation() const {
    return attenuation;
}

void Light::setAttenuation(const Vector3f &attenuation) {
    Light::attenuation = attenuation;
}

const Color &Light::getColor() const {
    return color;
}

void Light::setColor(const Color &color) {
    Light::color = color;
}

