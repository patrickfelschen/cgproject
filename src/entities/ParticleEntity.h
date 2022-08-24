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

    const Color &getColor() const;

    void setColor(const Color &c);

    float getLife() const;

    void setLife(float l);

    void setScale(float s);

private:
    const ParticleModel *model;
    Color color;
    float life;
    float maxLife;
    float scale;
};


#endif //CG_PARTICLEENTITY_H
