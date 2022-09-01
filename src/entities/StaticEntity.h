//
// Created by Patrick on 25.08.2022.
//

#ifndef CG_STATICENTITY_H
#define CG_STATICENTITY_H


#include "../models/ObjectModel.h"
#include "Entity.h"
#include "TerrainEntity.h"

class StaticEntity : public Entity {
public:
    explicit StaticEntity(const ObjectModel *model, const TerrainEntity *terrainEntity);

    ~StaticEntity() override;

    void update(float deltaTime) override;

    AABB getTransformedBoundingBox() const override;

    void render() override;

    void respawn();

    void setSpawnOffset(const Vector3f &spawnOffset);

private:
    const ObjectModel *model;
    const TerrainEntity *terrainEntity;

    Vector3f spawnOffset;
};


#endif //CG_STATICENTITY_H
