//
// Created by Patrick on 24.08.2022.
//

#ifndef CG_PARTICLEMANAGER_H
#define CG_PARTICLEMANAGER_H


#include <vector>
#include "entities/ParticleEntity.h"

class ParticleManager {
public:
    explicit ParticleManager(unsigned int numParticles);

    virtual ~ParticleManager();

    void update(const Entity *entity, float deltaTime);

    void render(const Camera &camera);

private:
    unsigned int numParticles;
    unsigned int lastUsedParticle = 0;
    std::vector<ParticleEntity *> particleEntities;

    unsigned int firstUnusedParticle();

    void respawnParticle(ParticleEntity *particle, const Entity *entity, Vector3f offset);

    float rndFloat(float min, float max);
};


#endif //CG_PARTICLEMANAGER_H
