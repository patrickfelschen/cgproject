//
// Created by Patrick on 11.08.2022.
//

#ifndef CG_GUNENTITY_H
#define CG_GUNENTITY_H


#include "Entity.h"
#include "EnemyEntity.h"
#include "../managers/GUIManager.h"

class GunEntity : public Entity {
public:
    explicit GunEntity(ObjectModel *model);

    ~GunEntity() override;

    void update(float deltaTime) override;

    AABB getTransformedBoundingBox() const override;

    void render() override;

    bool startShoot();

    void endShoot();

    void reload();

    void addMagazines(unsigned int count);

    void setAmmo(unsigned int count);

    void setMagazines(unsigned int count);

private:
    const ObjectModel *model;

    bool readyToFire;

    bool reloading;
    float reloadTime;
    float reloadTimer;

    unsigned int ammo;
    unsigned int maxAmmo;
    unsigned int magazines;
};


#endif //CG_GUNENTITY_H
