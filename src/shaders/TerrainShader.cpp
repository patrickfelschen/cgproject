//
// Created by Patrick on 17.08.2022.
//

#include "TerrainShader.h"

#define TO_RAD(deg) (deg * std::numbers::pi / 180.0)

#define VERT "../assets/shaders/terrainShader.vert"
#define FRAG "../assets/shaders/terrainShader.frag"

TerrainShader::TerrainShader() : Shader(VERT, FRAG) { }

TerrainShader::~TerrainShader() = default;

void TerrainShader::setUniforms() {
    // Transformation
    setUniform("uTransform", transform);
}
