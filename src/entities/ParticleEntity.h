//
// Created by Patrick on 24.08.2022.
//

#ifndef CG_PARTICLEENTITY_H
#define CG_PARTICLEENTITY_H


#include "Entity.h"
#include "../models/ParticleModel.h"

class ParticleEntity : public Entity {
public:
    explicit ParticleEntity(const ParticleModel *model);

    ~ParticleEntity() override;

    void update(float deltaTime) override;

    void render(const Camera &camera) override;

    Vector3f offset;
    Color color;
    float life;
    Vector3f velocity;
private:
    const ParticleModel *model;
};


#endif //CG_PARTICLEENTITY_H
