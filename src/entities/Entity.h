//
// Created by Patrick on 04.08.2022.
//

#ifndef CG_ENTITY_H
#define CG_ENTITY_H


#include "../models/ObjectModel.h"

class Entity {
public:
    explicit Entity(Model *model);

    virtual ~Entity();

    virtual void update(float deltaTime);

    virtual void render(const Camera &camera);

    void setPosition(float x, float y, float z);

    void setPosition(const Vector3f &pos);

    void setRotationX(float newRotationX);

    void setRotationY(float newRotationY);

    void setRotationZ(float newRotationZ);

    void setScaling(float newScaling);

    Model *getModel() const;

    const AABB getTransformedBoundingBox() const;


protected:
    Vector3f position;
    float rotationX;
    float rotationY;
    float rotationZ;
    float scaling;
private:
    Model *model;
};


#endif //CG_ENTITY_H
