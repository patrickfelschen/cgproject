//
// Created by Patrick on 26.08.2022.
//

#ifndef CG_TERRAINMANAGER_H
#define CG_TERRAINMANAGER_H


#include <vector>
#include "../entities/Entity.h"
#include "../entities/TerrainEntity.h"

class TerrainManager {
public:
    explicit TerrainManager(const TerrainEntity* terrainEntity);

    virtual ~TerrainManager();

    void update(float deltaTime);

    void render(const Camera& camera);

private:
    const TerrainEntity* terrainEntity;
    std::vector<Entity *> entities;
    ObjectModel *treeModel;
    ObjectModel *woodModel;
    ObjectModel *flowerRedModel;
    ObjectModel *flowerYellowModel;
    ObjectModel *lightPoleModel;
};


#endif //CG_TERRAINMANAGER_H
