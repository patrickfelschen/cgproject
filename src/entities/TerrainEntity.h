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

    void render(const Camera &camera) override;

    Vector3f getRandomPosition() const;
private:
    const TerrainModel *model;
};


#endif //CG_TERRAINENTITY_H
