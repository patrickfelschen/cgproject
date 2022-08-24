#ifndef CG_COINENTITY_H
#define CG_COINENTITY_H

#include "Entity.h"

class CoinEntity : public Entity {
public:
    explicit CoinEntity(const ObjectModel *model);

    ~CoinEntity() override;

    void update(float deltaTime) override;

    void render(const Camera &camera) override;

    float getDistanceToPlayer() const;

    void setDistanceToPlayer(float distance);

    void respawn(const Vector3f &playerPos);

    AABB getTransformedBoundingBox() const;

    bool hit = false;
private:
    float rotation = 0;
    float speed = 0;
    float distanceToPlayer = 0;

    float rndFloat(float min, float max);

    const ObjectModel *model;
};


#endif //CG_COINENTITY_H
