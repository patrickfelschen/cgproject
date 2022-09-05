//
// Created by Patrick on 03.08.2022.
//

#ifndef CG_CAMERA_H
#define CG_CAMERA_H

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "../maths/Matrix.h"
#include "../managers/SoundManager.h"
#include <numbers>

class Camera {
public:
    explicit Camera(GLFWwindow *window);

    virtual ~Camera();

    void update(float deltaTime);

    void setPosition(const Vector3f &newPosition);

    void setTarget(const Vector3f &newTarget);

    void setUp(const Vector3f &newUp);

    const Matrix &getView() const;

    const Matrix &getProj() const;

    Vector3f getPosition() const;

    Vector3f getTarget() const;

    Vector3f getUp() const;

    Vector3f getRight() const;

    void handleKeyboardInputs(float deltaTime);

    void handleMouseInputs(float mouseX, float mouseY);

private:
    GLFWwindow *window;

    int windowWidth = 0;
    int windowHeight = 0;

    Matrix view;
    Matrix proj;
    Vector3f position;
    Vector3f target;
    Vector3f up;

    float lastMouseX;
    float lastMouseY;

    float yaw;
    float pitch;
};


#endif //CG_CAMERA_H
