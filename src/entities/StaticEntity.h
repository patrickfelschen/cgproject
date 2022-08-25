//
// Created by Patrick on 25.08.2022.
//

#ifndef CG_STATICENTITY_H
#define CG_STATICENTITY_H


#include "../models/ObjectModel.h"
#include "Entity.h"

class StaticEntity : public Entity {
public:
    explicit StaticEntity(const ObjectModel *model);

    ~StaticEntity() override;

    void update(float deltaTime) override;

    void render(const Camera &camera) override;

private:
    const ObjectModel *model;
};


#endif //CG_STATICENTITY_H
