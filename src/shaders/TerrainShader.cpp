//
// Created by Patrick on 17.08.2022.
//

#include "TerrainShader.h"

#define VERT "../assets/shaders/terrainShader.vert"
#define FRAG "../assets/shaders/terrainShader.frag"

TerrainShader::TerrainShader() : Shader(VERT, FRAG) {
    this->projection.identity();
    this->transform.identity();
    this->view.identity();
}

TerrainShader::~TerrainShader() = default;

void TerrainShader::setUniforms() {
    setUniform("uProjection", projection);
    setUniform("uTransform", transform);
    setUniform("uView", view);
    // Kamera Position
    setUniform("uCamPos", cameraPosition);
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

void TerrainShader::setTransform(const Matrix &t) {
    this->transform = t;
}

void TerrainShader::setView(const Matrix &v) {
    this->view = v;
}

void TerrainShader::setProjection(const Matrix &p) {
    this->projection = p;
}

void TerrainShader::setCameraPosition(const Vector3f &c) {
    this->cameraPosition = c;
}
