//
// Created by Patrick on 24.08.2022.
//

#ifndef CG_TERRAINENTITY_H
#define CG_TERRAINENTITY_H


#include "../models/TerrainModel.h"
#include "Entity.h"

class TerrainEntity : public Entity {
public:
    explicit TerrainEntity(const TerrainModel *model);

    ~TerrainEntity() override;

    void update(float deltaTime) override;

    void render() override;

    AABB getTransformedBoundingBox() const override;

    Vector3f getRandomPosition(Vector3f offset = Vector3f()) const;

    float getHeightOfPosition(Vector3f position) const;
private:
    const TerrainModel *model;
};


#endif //CG_TERRAINENTITY_H
