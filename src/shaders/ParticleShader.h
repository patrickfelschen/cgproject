//
// Created by Patrick on 24.08.2022.
//

#ifndef CG_PARTICLESHADER_H
#define CG_PARTICLESHADER_H


#include "Shader.h"

class ParticleShader : public Shader {
public:
    ParticleShader();

    ~ParticleShader() override;

    const Matrix &getTransform() const;

    void setTransform(const Matrix &transform);

    const Matrix &getView() const;

    void setView(const Matrix &view);

    const Matrix &getProjection() const;

    void setProjection(const Matrix &projection);

    const Vector3f &getCameraPosition() const;

    void setCameraPosition(const Vector3f &cameraPosition);

    const Vector3f &getOffset() const;

    void setOffset(const Vector3f &offset);

    const Color &getColor() const;

    void setColor(const Color &color);

protected:
    void setUniforms() override;

private:
    Matrix transform;
    Matrix view;
    Matrix projection;
    Vector3f cameraPosition;
    Vector3f offset;
    Color color;
};


#endif //CG_PARTICLESHADER_H
