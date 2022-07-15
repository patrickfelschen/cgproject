#ifndef Entity_hpp
#define Entity_hpp

#include "../Models/TexturedModel.hpp"
#include "../Utils/Vector3f.h"

class Entity {
private:
    TexturedModel *model;
    Vector3f position;
    float rotX, rotY, rotZ;
    float scale;
public:
    Entity();

    Entity(TexturedModel *model, Vector3f position, float rotX, float rotY, float rotZ, float scale);

    ~Entity();

    TexturedModel *getModel();

    Vector3f getPosition();

    float getRotX() const;

    float getRotY() const;

    float getRotZ() const;

    float getScale() const;

    void setModel(TexturedModel *model);

    void setPosition(Vector3f pos);

    void setRotX(float rotX);

    void setRotY(float rotY);

    void setRotZ(float rotZ);

    void setScale(float scale);

    void increasePosition(float dx, float dy, float dz);

    void increaseRotation(float dx, float dy, float dz);
};

#endif