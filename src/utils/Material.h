//
// Created by Patrick on 17.08.2022.
//

#ifndef CG_MATERIAL_H
#define CG_MATERIAL_H

#include "Color.h"

class Material {
public:
    Material();

    virtual ~Material();

    Color diffuse;
    Color specular;
    Color ambient;
    float shininess;
};


#endif //CG_MATERIAL_H
