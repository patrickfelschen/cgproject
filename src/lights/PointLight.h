//
// Created by Patrick on 17.08.2022.
//

#ifndef CG_POINTLIGHT_H
#define CG_POINTLIGHT_H


#include "Light.h"

class PointLight : public Light {
public:
    PointLight();

    PointLight(const Vector3f &position, const Vector3f &attenuation, const Color &color);

    ~PointLight() override;

    LightType type() override;
};


#endif //CG_POINTLIGHT_H
