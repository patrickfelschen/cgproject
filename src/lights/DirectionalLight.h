//
// Created by Patrick on 17.08.2022.
//

#ifndef CG_DIRECTIONALLIGHT_H
#define CG_DIRECTIONALLIGHT_H


#include "Light.h"

class DirectionalLight : public Light {
public:
    DirectionalLight();

    DirectionalLight(const Vector3f &position,
                     const Vector3f &attenuation,
                     const Color &color,
                     const Vector3f &direction);

    ~DirectionalLight() override;

    LightType type() override;

protected:
    Vector3f direction;
};


#endif //CG_DIRECTIONALLIGHT_H
