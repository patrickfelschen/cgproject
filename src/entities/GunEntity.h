//
// Created by Patrick on 11.08.2022.
//

#ifndef CG_GUNENTITY_H
#define CG_GUNENTITY_H


#include "Entity.h"
#include "CoinEntity.h"

struct sortPosAsc {
    bool operator()(CoinEntity *c1, CoinEntity *c2) const {
        return c1->getDistanceToPlayer() < c2->getDistanceToPlayer();
    }
};

class GunEntity : public Entity {
public:
    explicit GunEntity(ObjectModel *model, GLFWwindow &window);

    ~GunEntity() override;

    void update(float deltaTime) override;

    void render(const Camera &camera) override;

    void setTargets(const std::vector<CoinEntity *> &v);

private:
    const ObjectModel *model;

    GLFWwindow &window;

    bool readyToFire = true;

    std::vector<CoinEntity *> targets;

    void shoot(const Camera &camera);
};


#endif //CG_GUNENTITY_H
