//
// Created by Patrick on 17.08.2022.
//

#include "TerrainShader.h"

#define vert "../assets/shaders/terrainShader.vert"
#define frag "../assets/shaders/terrainShader.frag"

TerrainShader::TerrainShader() : Shader(vert, frag, true) {}

TerrainShader::~TerrainShader() = default;

void TerrainShader::setUniforms(const Camera &camera) {
    Shader::setUniforms(camera);

    Vector3f lightPos = Vector3f(0.0f, 1.0f, 0.0f);

    setUniform("uLightPos", lightPos);
    setUniform("uCamPos", camera.getPosition());
    setUniform("uMaterial.ambientColor", Color(0.0f, 0.0f, 0.0f));
    setUniform("uMaterial.diffuseColor", Color(1.0f, 1.0f, 1.0f));
    setUniform("uMaterial.specularColor", Color(0.3f, 0.3f, 0.3f));
    setUniform("uMaterial.shininess", 10.0f);
}
