//
// Created by Patrick on 17.08.2022.
//

#ifndef CG_LIGHT_H
#define CG_LIGHT_H


#include "../maths/Vector3f.h"
#include "../utils/Color.h"

class Light {
public:
    enum LightType {
        POINT,
        DIRECTIONAL,
        SPOT
    };

    Light();

    Light(const Vector3f &position, const Vector3f &attenuation, const Color &color);

    virtual ~Light();

    const Vector3f &getPosition() const;

    void setPosition(const Vector3f &position);

    const Vector3f &getAttenuation() const;

    void setAttenuation(const Vector3f &attenuation);

    const Color &getColor() const;

    void setColor(const Color &color);

    virtual LightType type() = 0;

protected:
    Vector3f position;
    Vector3f attenuation;
    Color color;
};


#endif //CG_LIGHT_H
