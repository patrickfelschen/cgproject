#ifndef CG_ENEMYENTITY_H
#define CG_ENEMYENTITY_H

#include "Entity.h"

class EnemyEntity : public Entity {
public:
    explicit EnemyEntity(const ObjectModel *model);

    ~EnemyEntity() override;

    void update(float deltaTime) override;

    void render(const Camera &camera) override;

    float getDistanceToPlayer() const;

    void setDistanceToPlayer(float distance);

    void respawn(const Vector3f &playerPos);

    AABB getTransformedBoundingBox() const;

    void setTargetPosition(const Vector3f &targetPosition);

    bool hit = false;
private:
    float gravity = -9.81;
    float speed = 0;
    float distanceToPlayer = 0;
    Vector3f targetPosition;

    const ObjectModel *model;
};


#endif //CG_ENEMYENTITY_H