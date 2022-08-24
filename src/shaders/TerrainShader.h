//
// Created by Patrick on 17.08.2022.
//

#ifndef CG_TERRAINSHADER_H
#define CG_TERRAINSHADER_H


#include "Shader.h"

class TerrainShader : public Shader {
public:
    TerrainShader();

    ~TerrainShader() override;

    void setTransform(const Matrix &t);

    void setView(const Matrix &v);

    void setProjection(const Matrix &p);

    void setCameraPosition(const Vector3f &c);

protected:
    void setUniforms() override;

private:
    Matrix transform;
    Matrix view;
    Matrix projection;
    Vector3f cameraPosition;
};


#endif //CG_TERRAINSHADER_H
