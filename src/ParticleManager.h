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

    void update(float deltaTime);

    void render(const Camera &camera);

    void spawn(const Vector3f &origin);

private:
    std::vector<ParticleEntity *> particleEntities;

    float rndFloat(float min, float max);
};


#endif //CG_PARTICLEMANAGER_H
