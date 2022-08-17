//
// Created by Patrick on 17.08.2022.
//

#ifndef CG_MATERIAL_H
#define CG_MATERIAL_H


#include "Color.h"
#include "Texture.h"

class Material {
public:
    Material();

    virtual ~Material();

    Color diffuseColor;
    Color specularColor;
    Color ambientColor;
    float specularExponent;
    const Texture *diffuseTexture;
private:
};


#endif //CG_MATERIAL_H
