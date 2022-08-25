//
// Created by Patrick on 24.08.2022.
//

#include "ParticleManager.h"

ParticleManager::ParticleManager(unsigned int numParticles) {
    auto *model = new ParticleModel(new ParticleShader());

    for (unsigned int i = 0; i < numParticles; i++) {
        auto *particleEntity = new ParticleEntity(model);
        particleEntities.push_back(particleEntity);
    }
}

ParticleManager::~ParticleManager() {
    for (ParticleEntity *p: particleEntities) {
        delete p;
    }
}

void ParticleManager::update(float deltaTime) {
    for (ParticleEntity *p: particleEntities) {
        if (p->getLife() > 0.0f) {
//            printf("Alpha: %f\n", p->getColor().a);
            p->update(deltaTime);
        }
    }
}

void ParticleManager::render(const Camera &camera) {
    glEnable(GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    for (ParticleEntity *p: particleEntities) {
        if (p->getLife() > 0.0f) {
            p->render(camera);
        }
    }
    glDisable(GL_BLEND);
}

void ParticleManager::spawn(const Vector3f &origin) {
    for (ParticleEntity *p: particleEntities) {
        p->setPosition(origin);
        float x = rndFloat(-1.0, 1.0f);
        float y = rndFloat(-1.0, 1.0f);
        float z = rndFloat(-1.0, 1.0f);
        p->setPositionVelocity(Vector3f(x, y, z));
        p->setColor(1.0f);
        p->setLife(0.5f);
        p->setScale(rndFloat(0.001, 0.01));
    }
}

float ParticleManager::rndFloat(float min, float max) {
    return ((float(rand()) / float(RAND_MAX)) * (max - min)) + min;
}
