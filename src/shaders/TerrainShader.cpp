//
// Created by Patrick on 17.08.2022.
//

#include "TerrainShader.h"

#define TO_RAD(deg) (deg * std::numbers::pi / 180.0)

#define VERT "../assets/shaders/terrainShader.vert"
#define FRAG "../assets/shaders/terrainShader.frag"

TerrainShader::TerrainShader() : Shader(VERT, FRAG) {
    this->projection.identity();
    this->transform.identity();
    this->view.identity();
}

TerrainShader::~TerrainShader() = default;

void TerrainShader::setUniforms() {
    // Transformation
    setUniform("uProjection", projection);
    setUniform("uTransform", transform);
    setUniform("uView", view);
    // Kamera Position
    setUniform("uCamPos", cameraPosition);
    // Licht
//    setUniform("uDirLight.direction", Vector3f(0, -1.0f, 0));
//    setUniform("uDirLight.ambient", Color(0.05f, 0.05f, 0.05f));
//    setUniform("uDirLight.diffuse", Color(0.4f, 0.4f, 0.4f));
//    setUniform("uDirLight.specular", Color(0.5f, 0.5f, 0.5f));

    setUniform("uPointLight.position", Vector3f(0, 10, 0));
    setUniform("uPointLight.ambient", Color(0.05f, 0.05f, 0.05f));
    setUniform("uPointLight.diffuse", Color(0.8f, 0.8f, 0.8f));
    setUniform("uPointLight.specular", Color(0.6f, 0.6f, 0.6f));
    setUniform("uPointLight.constant", 1.0f);
    setUniform("uPointLight.linear", 0.09f);
    setUniform("uPointLight.quadratic", 0.032f);

    setUniform("uSpotLight.position", cameraPosition);
    setUniform("uSpotLight.direction", cameraDirection);
    setUniform("uSpotLight.ambient", Color(0.0f, 0.0f, 0.0f));
    setUniform("uSpotLight.diffuse", Color(1.0f, 1.0f, 1.0f));
    setUniform("uSpotLight.specular", Color(1.0f, 1.0f, 1.0f));
    setUniform("uSpotLight.constant", 1.0f);
    setUniform("uSpotLight.linear", 0.09f);
    setUniform("uSpotLight.quadratic", 0.032f);
    setUniform("uSpotLight.cutOff", static_cast<float>(cos(TO_RAD(12.5f))));
    setUniform("uSpotLight.outerCutOff", static_cast<float>(cos(TO_RAD(15.0f))));
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

void TerrainShader::setCameraDirection(const Vector3f &cameraDirection) {
    TerrainShader::cameraDirection = cameraDirection;
}
