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

    void setPosition(float x, float y, float z);

    void setPosition(const Vector3f &pos);

    void setRotationX(float newRotationX);

    void setRotationY(float newRotationY);

    void setRotationZ(float newRotationZ);

    void setScaling(float newScaling);

    const Vector3f &getPosition() const;

    float getRotAngleX() const;

    float getRotAngleY() const;

    float getRotAngleZ() const;

    float getScaleFactor() const;

protected:
    Matrix transformation;
    Vector3f position;
    float rotAngleX;
    float rotAngleY;
    float rotAngleZ;
    float scaleFactor;
};


#endif //CG_ENTITY_H
