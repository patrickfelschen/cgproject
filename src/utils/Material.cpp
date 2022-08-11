//
// Created by Patrick on 05.08.2022.
//

#include "Material.h"

Material::Material() {
    pDiffuse = nullptr;
    pSpecular = nullptr;
    ambientColor = Color(1.0f, 1.0f, 1.0f);
    diffuseColor = Color(1.0f, 1.0f, 1.0f);
    specularColor = Color(1.0f, 1.0f, 1.0f);
    shininess = 0;
}

Material::~Material() {

}
