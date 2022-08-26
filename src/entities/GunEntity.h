//
// Created by Patrick on 11.08.2022.
//

#ifndef CG_GUNENTITY_H
#define CG_GUNENTITY_H


#include "Entity.h"
#include "EnemyEntity.h"
#include "../managers/GUIManager.h"

struct sortPosAsc {
    bool operator()(EnemyEntity *c1, EnemyEntity *c2) const {
        return c1->getDistanceToPlayer() < c2->getDistanceToPlayer();
    }
};

class GunEntity : public Entity {
public:
    explicit GunEntity(ObjectModel *model);

    ~GunEntity() override;

    void update(float deltaTime) override;

    void render(const Camera &camera) override;

    void setTargets(const std::vector<EnemyEntity *> &v);

    void startShoot(const Camera &camera);

    void endShoot();

    void reload();

private:
    const ObjectModel *model;
    std::vector<EnemyEntity *> targets;

    float range = 20.0f;

    bool readyToFire = true;

    bool reloading = false;
    float reloadTime = 1.25f;
    float reloadTimer = 0;

    unsigned int ammo = 30;
    unsigned int maxAmmo = 30;
    unsigned int magazines = 5;
};


#endif //CG_GUNENTITY_H
