//
// Created by Patrick on 17.08.2022.
//

#include "DirectionalLight.h"

DirectionalLight::DirectionalLight() : Light() {
    this->direction = Vector3f(-1, -1, -1);
}

DirectionalLight::DirectionalLight(const Vector3f &position,
                                   const Vector3f &attenuation,
                                   const Color &color,
                                   const Vector3f &direction) : Light(position, attenuation, color) {
    this->direction = direction;
}

DirectionalLight::~DirectionalLight() = default;

Light::LightType DirectionalLight::type() {
    return DIRECTIONAL;
}
