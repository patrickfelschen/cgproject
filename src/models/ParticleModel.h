//
// Created by Patrick on 24.08.2022.
//

#ifndef CG_PARTICLEMODEL_H
#define CG_PARTICLEMODEL_H


#include "Model.h"
#include "../shaders/ParticleShader.h"

class ParticleModel : public Model {
public:
    explicit ParticleModel(ParticleShader *shader);

    ~ParticleModel() override;

    ParticleShader *shader;

    void render() const override;
};


#endif //CG_PARTICLEMODEL_H
