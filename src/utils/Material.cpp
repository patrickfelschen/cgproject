//
// Created by Patrick on 17.08.2022.
//

#include "Material.h"

/**
 * Standard Materialeigenschaften
 * Weitere Materialeigenschaften unter:
 * http://devernay.free.fr/cours/opengl/materials.html
 */
Material::Material() {
    this->diffuse = Color(0.8f, 0.8f, 0.8f);
    this->specular = Color(0.5f, 0.5f, 0.5f);
    this->ambient = Color(0.3f, 0.3f, 0.3f);
    this->shininess = 1.0f;
}

Material::~Material() = default;
