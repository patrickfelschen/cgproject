//
// Created by Patrick on 24.08.2022.
//

#ifndef CG_SKYBOXENTITY_H
#define CG_SKYBOXENTITY_H


#include "Entity.h"

class SkyboxEntity : public Entity {
public:
    explicit SkyboxEntity(const ObjectModel *model);

    ~SkyboxEntity() override;

    void render(const Camera &camera) override;

private:
    const ObjectModel *model;
};


#endif //CG_SKYBOXENTITY_H
