//
// Created by Patrick on 05.08.2022.
//

#ifndef CG_PHONGSHADER_H
#define CG_PHONGSHADER_H


#include "Shader.h"

class PhongShader : public Shader {
public:
    PhongShader();

    ~PhongShader() override;

    void setTransform(const Matrix &t);

    void setView(const Matrix &v);

    void setProjection(const Matrix &p);

    void setCameraPosition(const Vector3f &c);

    void setCameraDirection(const Vector3f &cameraDirection);

protected:
    void setUniforms() override;

private:
    Matrix transform;
    Matrix view;
    Matrix projection;
    Vector3f cameraPosition;
    Vector3f cameraDirection;
};


#endif //CG_PHONGSHADER_H
