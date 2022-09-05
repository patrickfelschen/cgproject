//
// Created by Patrick on 17.08.2022.
//

#include "TerrainShader.h"

#define VERT "../assets/Shaders/terrainShader.vert"
#define FRAG "../assets/Shaders/terrainShader.frag"

TerrainShader::TerrainShader() : Shader(VERT, FRAG) {}

TerrainShader::~TerrainShader() = default;

/**
 * Transformations Matrix in den Shader laden
 */
void TerrainShader::setUniforms() {
    // Transformation
    setUniform("uTransform", transform);
}
