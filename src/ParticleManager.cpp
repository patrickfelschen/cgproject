//
// Created by Patrick on 24.08.2022.
//

#include "ParticleManager.h"

ParticleManager::ParticleManager(unsigned int numParticles) {
    this->numParticles = numParticles;

    auto *model = new ParticleModel(new ParticleShader());

    for (unsigned int i = 0; i < numParticles; ++i) {
        auto *entity = new ParticleEntity(model);
        entity->setPosition(Vector3f(0.0f, 0.0f, -10.0f));
        particleEntities.push_back(entity);
    }
}

ParticleManager::~ParticleManager() {

}

void ParticleManager::update(const Entity *entity, float deltaTime) {
    for (ParticleEntity *p: particleEntities) {
        unsigned int unusedParticle = firstUnusedParticle();
        respawnParticle(particleEntities[unusedParticle], entity, Vector3f(0.0f, 0.0f, -10.0f));
    }

    for (ParticleEntity *p: particleEntities) {
        p->life = (p->life - deltaTime);
        if (p->life > 0.0f) {
            p->setPosition(p->getPosition() - p->velocity * deltaTime);
            p->color.a = (p->color.a - deltaTime);
            printf("Alpha: %f\n", p->color.a);
        }
    }
}

void ParticleManager::render(const Camera &camera) {
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    for (ParticleEntity *p: particleEntities) {
        if (p->life > 0.0f) {
            p->render(camera);
        }
    }
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

unsigned int ParticleManager::firstUnusedParticle() {
    for (unsigned int i = lastUsedParticle; i < numParticles; i++) {
        if (particleEntities[i]->life <= 0.0f) {
            lastUsedParticle = i;
            return i;
        }
    }

    lastUsedParticle = 0;
    return 0;
}

void ParticleManager::respawnParticle(ParticleEntity *particle, const Entity *entity, Vector3f offset) {
    float random = rndFloat(-1.0f, 1.0f);
    float rColor = 0.5f + ((rand() % 100) / 100.0f);
    particle->setPosition(entity->getPosition()); //(Vector3f(0.026, -0.015, -0.045));
    particle->color = Color(rColor, rColor, rColor, 1.0f);
    particle->life = 2.0f;
    particle->velocity = Vector3f(rndFloat(-0.025f, 0.025f), rndFloat(-0.025f, 0.025f), rndFloat(0.2f, 3.0f));
}

float ParticleManager::rndFloat(float min, float max) {
    return ((float(rand()) / float(RAND_MAX)) * (max - min)) + min;
}
