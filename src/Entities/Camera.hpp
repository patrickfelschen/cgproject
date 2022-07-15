#ifndef Camera_HPP
#define Camera_HPP

#include "../Utils/Vector3f.h"
#include "../GLincludes.hpp"


class Camera {
private:
    Vector3f pos;
    float yaw, pitch, roll;
public:
    Camera();

    Camera(Vector3f pos);

    ~Camera();

    Vector3f getPosition();

    float getYaw();

    float getPitch();

    float getRoll();

    void move(int key);
};

#endif
