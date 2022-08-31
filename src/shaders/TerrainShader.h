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

protected:
    void setUniforms() override;

private:
    Matrix transform;
};


#endif //CG_TERRAINSHADER_H
