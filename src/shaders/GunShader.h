//
// Created by Patrick on 31.08.2022.
//

#ifndef CG_GUNSHADER_H
#define CG_GUNSHADER_H


#include "Shader.h"

class GunShader : public Shader {
public:
    GunShader();

    ~GunShader() override;

protected:
    void setUniforms() override;

};


#endif //CG_GUNSHADER_H
