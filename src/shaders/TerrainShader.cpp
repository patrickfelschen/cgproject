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
    // Kamera Position
    setUniform("uCamPos", camera.getPosition());
    // Licht
    Vector3f lightPos = Vector3f(-3.0f, 10.0f, 0.0f);
    Color light = Color(1.0f, 1.0f, 1.0f);
    Color lightDiffuse = light * 0.8;
    Color lightAmbient = lightDiffuse * 0.7f;
    Color lightSpecular = Color(1.0f, 1.0f, 1.0f);

    setUniform("uLight.position", lightPos);
    setUniform("uLight.ambient", lightAmbient);
    setUniform("uLight.diffuse", lightDiffuse);
    setUniform("uLight.specular", lightSpecular);
}
