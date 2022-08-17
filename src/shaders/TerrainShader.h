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

protected:
    void setUniforms(const Camera &camera) override;
};


#endif //CG_TERRAINSHADER_H
