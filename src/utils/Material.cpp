//
// Created by Patrick on 17.08.2022.
//

#include "Material.h"

Material::Material() {
    this->diffuse = Color(0.8f, 0.8f, 0.8f, 1.0f);
    this->specular = Color(0.5f, 0.5f, 0.5f, 1.0f);
    this->ambient = Color(0.3f, 0.3f, 0.3f, 1.0f);
    this->shininess = 1.0f;
}

Material::~Material() = default;
