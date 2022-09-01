#ifndef CG_ENEMYENTITY_H
#define CG_ENEMYENTITY_H

#include "Entity.h"
#include "TerrainEntity.h"
#include "../managers/SoundManager.h"

class EnemyEntity : public Entity {
public:
    explicit EnemyEntity(const ObjectModel *model, const TerrainEntity* terrainEntity);

    ~EnemyEntity();

    void update(float deltaTime) override;

    void render() override;

    void respawn();

    AABB getTransformedBoundingBox() const override;

    void setTargetPosition(const Vector3f &targetPosition);

    void setSpeed(float speed);

    bool isDead() const;

    void decreaseLife(unsigned int value);

    irrklang::ISound *getSound() const;

private:
    const ObjectModel *model;
    const TerrainEntity *terrainEntity;

    unsigned int life = 1;
    unsigned int maxLife = 1;

    float yawOffset = 90;
    float pitchOffset = 20;

    float speed = 1.0f;
    float groundOffset = 0.2f;
    Vector3f targetPosition;

    irrklang::ISound *sound;
};


#endif //CG_ENEMYENTITY_H