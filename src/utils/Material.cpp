//
// Created by Patrick on 17.08.2022.
//

#include "Material.h"

Material::Material() {
    this->diffuseColor = Color(1.0f, 1.0f, 1.0f);
    this->specularColor = Color(0.3f, 0.3f, 0.3f);
    this->ambientColor = Color(0.0f, 0.0f, 0.0f);
    this->specularExponent = 10;
    this->diffuseTexture = nullptr;
}

Material::~Material() {

}
