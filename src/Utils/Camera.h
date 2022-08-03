//
// Created by Patrick on 03.08.2022.
//

#ifndef CG_CAMERA_H
#define CG_CAMERA_H

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "../maths/Matrix.h"
#include <numbers>

class Camera {
public:
    explicit Camera(GLFWwindow &window);

    virtual ~Camera();

    void update(float deltaTime);

    Vector3f getPosition();

    Vector3f getTarget();

    Vector3f getUp() const;

    void setPosition(const Vector3f &newPosition);

    void setTarget(const Vector3f &newTarget);

    void setUp(const Vector3f &newUp);

    const Matrix &getView() const;

    const Matrix &getProj() const;

private:
    GLFWwindow &window;

    Matrix view;
    Matrix proj;
    Vector3f position;
    Vector3f target;
    Vector3f up;

    float lastMouseX;
    float lastMouseY;

    float yaw;
    float pitch;

    void handleKeyboardInputs(float deltaTime);

    void handleMouseInputs(float deltaTime);
};


#endif //CG_CAMERA_H
