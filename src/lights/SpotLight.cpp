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


