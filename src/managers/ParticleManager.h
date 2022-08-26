//
// Created by Patrick on 24.08.2022.
//

#ifndef CG_PARTICLEMANAGER_H
#define CG_PARTICLEMANAGER_H


#include <vector>
#include "../entities/ParticleEntity.h"

class ParticleManager {
public:
    explicit ParticleManager(unsigned int numParticles);

    virtual ~ParticleManager();

    void update(float deltaTime);

    void render(const Camera &camera);

    void spawn(const Vector3f &origin, Color color);

private:
    std::vector<ParticleEntity *> particleEntities;
};


#endif //CG_PARTICLEMANAGER_H
