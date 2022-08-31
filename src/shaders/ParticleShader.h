//
// Created by Patrick on 24.08.2022.
//

#ifndef CG_PARTICLESHADER_H
#define CG_PARTICLESHADER_H


#include "Shader.h"

class ParticleShader : public Shader {
public:
    ParticleShader();

    ~ParticleShader() override;

    void setColor(const Color &c);

    void setScale(float scale);

protected:
    void setUniforms() override;

private:
    Color color;
    float scale;
};


#endif //CG_PARTICLESHADER_H
