//
// Created by Patrick on 17.08.2022.
//

#include "PointLight.h"

PointLight::PointLight() : Light() {}

PointLight::PointLight(const Vector3f &position, const Vector3f &attenuation, const Color &color) : Light(position,
                                                                                                          attenuation,
                                                                                                          color) {}

Light::LightType PointLight::type() {
    return POINT;
}

PointLight::~PointLight() = default;
