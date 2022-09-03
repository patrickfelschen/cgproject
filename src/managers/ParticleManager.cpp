//
// Created by Patrick on 24.08.2022.
//

#include "ParticleManager.h"
#include "../maths/Random.h"

/**
 * Erzeugt Partikel-Einheiten und fügt sie zu particleEntities hinzu
 * @param numParticles Anzahl der Partikel
 */
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

/**
 * Aktualisiert alle lebenden Partikel
 * @param deltaTime Zeitunterschied zum letzten Frame
 */
void ParticleManager::update(float deltaTime) {
    for (ParticleEntity *p: particleEntities) {
        if (p->getLife() > 0.0f) {
            //printf("Alpha: %f\n", p->getColor().a);
            p->update(deltaTime);
        }
    }
}

void ParticleManager::render() {
    // https://learnopengl.com/Advanced-OpenGL/Blending
    // "Mischt" die Alpha-Werte eines Fragmentes
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    for (ParticleEntity *p: particleEntities) {
        if (p->getLife() > 0.0f) {
            p->render();
        }
    }
    glDisable(GL_BLEND);
}

/**
 * Erzeugt einen Partikeleffekt
 * @param origin Ursprung der Partikel
 * @param color Farbe der Partikel
 */
void ParticleManager::spawn(const Vector3f &origin, Color color) {
    for (ParticleEntity *p: particleEntities) {
        p->setPosition(origin);
        float x = Random::randFloat(-1.0, 1.0f);
        float y = Random::randFloat(-1.0, 1.0f);
        float z = Random::randFloat(-1.0, 1.0f);
        // Zufällige Bewegungsrichtung
        p->setPositionVelocity(Vector3f(x, y, z));
        p->setColor(color);
        p->setLife(Random::randFloat(0.2, 0.5));
        p->setScaling(Random::randFloat(0.005, 0.01));
    }
}
