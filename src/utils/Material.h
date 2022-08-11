//
// Created by Patrick on 05.08.2022.
//

#ifndef CG_MATERIAL_H
#define CG_MATERIAL_H


#include "color.h"
#include "../textures/Texture.h"

class Material {
public:
    Material();

    virtual ~Material();

    Texture *pDiffuse;
    Texture *pSpecular;
    Color ambientColor;
    Color diffuseColor;
    Color specularColor;
    float shininess;
};


#endif //CG_MATERIAL_H
