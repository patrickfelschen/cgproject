//
// Created by Patrick on 12.08.2022.
//

#ifndef CG_TERRAINMODEL_H
#define CG_TERRAINMODEL_H


#include "../shaders/Shader.h"
#include "Model.h"

class TerrainModel : public Model {
public:
    explicit TerrainModel(Shader *shader);

    ~TerrainModel() override = default;

    void update(float deltaTime) const override;

    void render(const Camera &camera, const Matrix &transform) const override;

private:
    float width;
    float height;
    float depth;

    void generate();
};


#endif //CG_TERRAINMODEL_H
