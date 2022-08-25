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

    const float getHeightOfTerrain(float worldX, float worldZ) const;

    float getSize() const;

private:
    unsigned int imgWidth;
    unsigned int imgHeight;

    float size;
    float width;
    float height;
    float depth;

    std::vector<float> heights;

    float baryCentric(Vector3f p1, Vector3f p2, Vector3f p3, Vector2f pos) const;

    void generate();
};


#endif //CG_TERRAINMODEL_H
