//
// Created by Patrick on 03.08.2022.
// https://learnopengl.com/code_viewer_gh.php?code=includes/learnopengl/camera.h
//


#include "Camera.h"

#define TO_RAD(deg) (deg * std::numbers::pi / 180.0)
#define TO_DEG(rad) (rad * 180.0 / std::numbers::pi)

Camera::Camera(GLFWwindow &window) : window(window) {
    position = Vector3f(0.0f, 0.0f, 0.0f);
    target = Vector3f(0.0f, 0.0f, -1.0f);
    up = Vector3f(0.0f, 1.0f, 0.0f);

    yaw = 0;
    pitch = 0;

    int windowWidth, windowHeight;
    glfwGetWindowSize(&window, &windowWidth, &windowHeight);

    lastMouseX = (float) windowWidth / 2;
    lastMouseY = (float) windowHeight / 2;

    view.identity();
    proj.perspective(
            TO_RAD(65),
            (float) windowWidth / (float) windowHeight,
            0.045f,
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

Vector3f Camera::getTarget() {
    target.x = cos(TO_RAD(yaw)) * cos(TO_RAD(pitch));
    target.y = sin(TO_RAD(pitch));
    target.z = sin(TO_RAD(yaw)) * cos(TO_RAD(pitch));

    target.normalize();

    return target;
}

Vector3f Camera::getUp() const {
    return up;
}

void Camera::update(float deltaTime) {
    handleKeyboardInputs(deltaTime);
    handleMouseInputs(deltaTime);

    view.lookAt(getTarget() + getPosition(), getUp(), getPosition());
}

void Camera::handleKeyboardInputs(float deltaTime) {
    float speed = 0.5f * deltaTime;

    if (glfwGetKey(&window, GLFW_KEY_W) == GLFW_PRESS) {
        position += (target * speed);
    }
    if (glfwGetKey(&window, GLFW_KEY_S) == GLFW_PRESS) {
        position -= (target * speed);
    }
    if (glfwGetKey(&window, GLFW_KEY_A) == GLFW_PRESS) {
        position -= getRight() * speed;
    }
    if (glfwGetKey(&window, GLFW_KEY_D) == GLFW_PRESS) {
        position += getRight() * speed;
    }
    if (glfwGetKey(&window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        position.y += speed;
    }
    if (glfwGetKey(&window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
        position.y -= speed;
    }
}

void Camera::handleMouseInputs(float deltaTime) {
    double mouseX, mouseY;
    glfwGetCursorPos(&window, &mouseX, &mouseY);

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

Vector3f Camera::getRight() {
    return getTarget().cross(getUp()).normalize();
}



