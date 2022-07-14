#include "StaticShader.hpp"

const std::string  StaticShader::VERTEX_FILE = ASSET_DIRECTORY"Shaders/vertexShader.glsl";
const std::string  StaticShader::FRAGMENT_FILE = ASSET_DIRECTORY"Shaders/fragmentShader.glsl";

StaticShader::StaticShader() : ShaderProgram(VERTEX_FILE, FRAGMENT_FILE) {
    this->bindAttributes();
    this->getAllUniformLocations();
}

StaticShader::~StaticShader() {

}

void StaticShader::loadTransformationMatrix(const Matrix &matrix) {
    ShaderProgram::loadMatrix(location_transformationMatrix, matrix);
}

void StaticShader::loadProjectionMatrix(const Matrix &projection) {
    ShaderProgram::loadMatrix(location_projectionMatrix, projection);
}

void StaticShader::loadViewMatrix(Camera camera) {
    Matrix viewMatrix = Maths::createViewMatrix(camera);
    ShaderProgram::loadMatrix(location_viewMatrix, viewMatrix);
}

void StaticShader::bindAttributes() {
    ShaderProgram::bindAttribute(0, "position");
    ShaderProgram::bindAttribute(1, "textureCoords");
}

void StaticShader::getAllUniformLocations() {
    location_transformationMatrix = ShaderProgram::getUniformLocation("transformationMatrix");
    location_projectionMatrix = ShaderProgram::getUniformLocation("projectionMatrix");
    location_viewMatrix = ShaderProgram::getUniformLocation("viewMatrix");
}
