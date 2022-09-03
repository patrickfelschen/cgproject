//
// Created by Patrick on 03.08.2022.
// https://learnopengl.com/code_viewer_gh.php?code=includes/learnopengl/camera.h
//


#include "Camera.h"
#include "../managers/SoundManager.h"

#define TO_RAD(deg) (deg * std::numbers::pi / 180.0)

Camera::Camera(GLFWwindow *window) : window(window) {
    position = Vector3f(0.0f, 0.0f, 0.0f);
    target = Vector3f(0.0f, 0.0f, -1.0f);
    up = Vector3f(0.0f, 1.0f, 0.0f);

    yaw = 0;
    pitch = 0;

    glfwGetWindowSize(window, &windowWidth, &windowHeight);

    lastMouseX = (float) windowWidth / 2;
    lastMouseY = (float) windowHeight / 2;

    view.identity();
    proj.perspective(
            TO_RAD(65),
            (float) windowWidth / (float) windowHeight,
            0.001f,
            1000.0f
    );
}

Camera::~Camera() = default;

const Matrix &Camera::getView() const {
    return view;
}

const Matrix &Camera::getProj() const {
    return proj;
}

void Camera::setPosition(const Vector3f &newPosition) {
    position = newPosition;
}

void Camera::setTarget(const Vector3f &newTarget) {
    target = newTarget;
}

void Camera::setUp(const Vector3f &newUp) {
    this->up = newUp;
}

Vector3f Camera::getPosition() const {
    return position;
}

Vector3f Camera::getTarget() const {
    return target;
}

Vector3f Camera::getUp() const {
    return up;
}

Vector3f Camera::getRight() const {
    return target.cross(up).normalize();
}

void Camera::update(float deltaTime) {
    handleKeyboardInputs(deltaTime);
    target.x = cos(TO_RAD(yaw)) * cos(TO_RAD(pitch));
    target.y = sin(TO_RAD(pitch));
    target.z = sin(TO_RAD(yaw)) * cos(TO_RAD(pitch));
    target.normalize();
    view.lookAt(target + position, up, position);
}

void Camera::handleKeyboardInputs(float deltaTime) {
    float speed = 3.0f * deltaTime;
    bool soundPlaying = false;

    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
        speed *= 1.5;
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        soundPlaying = true;
        position += (target * speed);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        soundPlaying = true;
        position -= (target * speed);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        soundPlaying = true;
        position -= getRight() * speed;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        soundPlaying = true;
        position += getRight() * speed;
    }
//    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
//        position.y += speed;
//    }

    if (soundPlaying) {
        SoundManager::getInstance().play2DSound("../assets/Sounds/step.mp3", false, true);
    } else {
        SoundManager::getInstance().stopSound("../assets/Sounds/step.mp3");
    }
}

void Camera::handleMouseInputs(float mouseX, float mouseY) {
    float xOffset = mouseX - lastMouseX;
    float yOffset = lastMouseY - mouseY;  // reversed since y-coordinates range from bottom to top

    lastMouseX = (float) mouseX;
    lastMouseY = (float) mouseY;

    const float sensitivity = 0.1f;
    xOffset *= sensitivity;
    yOffset *= sensitivity;

    yaw += xOffset;
    pitch += yOffset;

    if (pitch > 89.0f) pitch = 89.0f;
    if (pitch < -89.0f) pitch = -89.0f;
}
