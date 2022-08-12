//
// Created by Patrick on 11.08.2022.
//

#ifndef CG_GUNENTITY_H
#define CG_GUNENTITY_H


#include "Entity.h"

class GunEntity : public Entity {
public:
    explicit GunEntity(Model *model);

    ~GunEntity() override;

    void update(float deltaTime) override;

    void render(const Camera &camera);
};


#endif //CG_GUNENTITY_H
