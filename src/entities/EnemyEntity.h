#ifndef CG_ENEMYENTITY_H
#define CG_ENEMYENTITY_H

#include "Entity.h"
#include "TerrainEntity.h"
#include "../managers/SoundManager.h"
#include "../maths/Random.h"

class EnemyEntity : public Entity {
public:
    explicit EnemyEntity(const ObjectModel *model, const TerrainEntity *terrainEntity);

    ~EnemyEntity() override;

    void update(float deltaTime) override;

    void render() override;

    void respawn();

    AABB getTransformedBoundingBox() const override;

    void setTargetPosition(const Vector3f &targetPosition);

    void increaseSpeed(float value);

    void setSpeed(float speed);

    bool isDead() const;

    void decreaseLife(unsigned int value);

    void increaseMaxLife(unsigned int value);

    unsigned int getLife() const;

    unsigned int getMaxLife() const;

    irrklang::ISound *getSound() const;

    void setMaxLife(unsigned int maxLife);

private:
    const ObjectModel *model;
    const TerrainEntity *terrainEntity;
    irrklang::ISound *sound;

    unsigned int life = 1;
    unsigned int maxLife;

    float yawOffset = 90;
    float pitchOffset = 20;

    float speed = 1.0f;
    float groundOffset = 0.2f;
    Vector3f targetPosition;
};


#endif //CG_ENEMYENTITY_H