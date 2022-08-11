//
// Created by Patrick on 04.08.2022.
//

#include "Model.h"

Model::Model(Shader *shader) : shader(shader) {}

Model::~Model() = default;

void Model::update(float deltaTime) {
}

void Model::render(const Camera &camera) {
    Matrix transformation = translation * rotationX * rotationY * rotationZ * scaling;
    shader->setModelTransform(transformation);
}

void Model::translate(const Vector3f &v) {
    translation.translation(v);
}

void Model::scale(const float &v) {
    scaling.scale(v);
}

void Model::rotateX(float angle) {
    rotationX.rotationX(angle);
}

void Model::rotateY(float angle) {
    rotationY.rotationY(angle);
}

void Model::rotateZ(float angle) {
    rotationZ.rotationZ(angle);
}


