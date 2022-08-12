//
// Created by Patrick on 05.08.2022.
//

#ifndef CG_PHONGSHADER_H
#define CG_PHONGSHADER_H


#include "Shader.h"

class PhongShader : public Shader {
public:
    PhongShader();

    PhongShader(bool useView);

    ~PhongShader() override;

protected:
    void setUniforms(const Camera &camera) override;

private:
    Vector3f lightPos;
};


#endif //CG_PHONGSHADER_H
