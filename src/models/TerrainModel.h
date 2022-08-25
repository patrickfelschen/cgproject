//
// Created by Patrick on 12.08.2022.
//

#ifndef CG_TERRAINMODEL_H
#define CG_TERRAINMODEL_H


#include "../shaders/Shader.h"
#include "Model.h"
#include "../shaders/TerrainShader.h"

class TerrainModel : public Model {
public:
    explicit TerrainModel(TerrainShader *shader);

    ~TerrainModel() override = default;

    void render() const override;

    TerrainShader *shader;

private:

    float width;
    float height;
    float depth;

    void generate();
};


#endif //CG_TERRAINMODEL_H
