//
// Created by Patrick on 04.08.2022.
//

#ifndef CG_ENTITY_H
#define CG_ENTITY_H


#include "../models/ObjectModel.h"

class Entity {
public:
    explicit Entity();

    virtual ~Entity();

    virtual void update(float deltaTime);

    virtual void render(const Camera &camera) = 0;

    void setPosition(const Vector3f &pos);

    void setScaling(float newScaling);

    const Vector3f &getPosition() const;

    void setPositionVelocity(const Vector3f &positionVelocity);

    void setRotationVelocity(const Vector3f &rotationVelocity);

protected:
    Matrix transformation;

    Vector3f position;
    Vector3f positionVelocity;

    Vector3f rotation;
    Vector3f rotationVelocity;

    float scaleFactor;

    void setRotation(const Vector3f rot);
};


#endif //CG_ENTITY_H
