//
// Created by Patrick on 17.08.2022.
//

#ifndef CG_SPOTLIGHT_H
#define CG_SPOTLIGHT_H


#include "../maths/Vector3f.h"
#include "Light.h"

class SpotLight : Light {
public:
    SpotLight();

    SpotLight(const Vector3f &position, const Vector3f &attenuation, const Color &color, const Vector3f &direction,
              float innerRadius, float outerRadius);

protected:
    Vector3f direction;
    float innerRadius;
    float outerRadius;
};


#endif //CG_SPOTLIGHT_H
