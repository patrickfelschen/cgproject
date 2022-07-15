#include "Camera.hpp"

Camera::Camera() {
    this->pos = Vector3f(0, 0, 0);
    this->yaw = 0;
    this->pitch = 0;
    this->roll = 0;
}

Camera::Camera(Vector3f pos) {
    this->pos = pos;
}

Camera::~Camera() {
}

Vector3f Camera::getPosition() {
    return this->pos;
}

float Camera::getYaw() {
    return this->yaw;
}

float Camera::getPitch() {
    return this->pitch;
}

float Camera::getRoll() {
    return this->roll;
}

void Camera::move(int key) {
    switch (key) {
        case GLFW_KEY_W:
            pos.Z -= 0.02f;
            break;
        case GLFW_KEY_A:
            pos.X -= 0.02f;
            break;
        case GLFW_KEY_S:
            pos.Z += 0.02f;
            break;
        case GLFW_KEY_D:
            pos.X += 0.02f;
            break;
    }
}
