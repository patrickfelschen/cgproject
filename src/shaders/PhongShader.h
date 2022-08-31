//
// Created by Patrick on 05.08.2022.
//

#ifndef CG_PHONGSHADER_H
#define CG_PHONGSHADER_H


#include "Shader.h"

class PhongShader : public Shader {
public:
    PhongShader();

    ~PhongShader() override;

    void setTransform(const Matrix &t);

protected:
    void setUniforms() override;

private:
    Matrix transform;
};


#endif //CG_PHONGSHADER_H
