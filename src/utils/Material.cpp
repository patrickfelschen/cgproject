//
// Created by Patrick on 17.08.2022.
//

#include "Material.h"

Material::Material() {
    this->diffuse = Color(1.0f, 1.0f, 1.0f, 1.0f);
    this->specular = Color(0.3f, 0.3f, 0.3f, 1.0f);
    this->ambient = Color(0.1f, 0.1f, 0.1f, 1.0f);
    this->shininess = 1.0f;
}

Material::~Material() = default;
