//
// Created by Patrick on 17.08.2022.
//

#include "SpotLight.h"

SpotLight::SpotLight() {
    this->direction = Vector3f(-1, -1, -1);
    this->innerRadius = 30.0f;
    this->outerRadius = 40.0f;
}

SpotLight::SpotLight(const Vector3f &position,
                     const Vector3f &attenuation,
                     const Color &color,
                     const Vector3f &direction,
                     float innerRadius,
                     float outerRadius) : Light(position, attenuation, color) {
    this->direction = direction;
    this->innerRadius = innerRadius;
    this->outerRadius = outerRadius;
}

Light::LightType SpotLight::type() {
    return SPOT;
}

const Vector3f &SpotLight::getDirection() const {
    return direction;
}

void SpotLight::setDirection(const Vector3f &direction) {
    SpotLight::direction = direction;
}

float SpotLight::getInnerRadius() const {
    return innerRadius;
}

void SpotLight::setInnerRadius(float innerRadius) {
    SpotLight::innerRadius = innerRadius;
}

float SpotLight::getOuterRadius() const {
    return outerRadius;
}

void SpotLight::setOuterRadius(float outerRadius) {
    SpotLight::outerRadius = outerRadius;
}


