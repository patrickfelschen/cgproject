//
// Created by Patrick on 01.09.2022.
//

#ifndef CG_PLAYERENTITY_H
#define CG_PLAYERENTITY_H


#include "GunEntity.h"
#include "Entity.h"
#include "StaticEntity.h"
#include "../managers/ParticleManager.h"

class PlayerEntity : Entity {
public:
    explicit PlayerEntity(const Camera *camera);

    ~PlayerEntity() override;

    void render() override;

    void update(float deltaTime) override;

    unsigned int getHitCount() const;

    AABB getTransformedBoundingBox() const override;

    void setGunEntity(GunEntity *gunEntity);

    void init();

    void increaseLife(unsigned int value);

    void decreaseLife(unsigned int value);

    bool isAlive() const;

    void setEnemies(const std::vector<EnemyEntity *> &enemies);

    void setMedicCases(const std::vector<StaticEntity *> &medicCases);

    void setMagazineCases(const std::vector<StaticEntity *> &magazineCases);

    void startShoot();

    void endShoot();

    void reload();

    void increaseMagazines(unsigned int count);

    bool checkEntityRayCollision(Entity *entity, const Ray &ray, float range) const;

    bool checkEntityPositionCollision(Entity *entity1, Entity *entity2, float offset) const;

private:
    const Camera *camera;

    GunEntity *gunEntity;

    std::vector<EnemyEntity *> enemies;

    std::vector<StaticEntity *> medicCases;

    std::vector<StaticEntity *> magazineCases;

    ParticleManager *particleManager;

    unsigned int maxLife;
    unsigned int life;

    unsigned int hitCount;
};


#endif //CG_PLAYERENTITY_H
