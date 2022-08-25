//
// Created by Patrick on 11.08.2022.
//

#ifndef CG_GUNENTITY_H
#define CG_GUNENTITY_H


#include "Entity.h"
#include "CoinEntity.h"
#include "../gui/GUIManager.h"

struct sortPosAsc {
    bool operator()(CoinEntity *c1, CoinEntity *c2) const {
        return c1->getDistanceToPlayer() < c2->getDistanceToPlayer();
    }
};

class GunEntity : public Entity {
public:
    explicit GunEntity(ObjectModel *model);

    ~GunEntity() override;

    void update(float deltaTime) override;

    void render(const Camera &camera) override;

    void setTargets(const std::vector<CoinEntity *> &v);

    void startShoot(const Camera &camera);

    void endShoot();

    void reload();

private:
    const ObjectModel *model;
    std::vector<CoinEntity *> targets;

    float range = 10.0f;

    bool readyToFire = true;

    bool reloading = false;
    float reloadTime = 0.5f ;
    float reloadTimer = 0;

    unsigned int ammo = 30;
    unsigned int maxAmmo = 30;
    unsigned int magazines = 5;
};


#endif //CG_GUNENTITY_H
