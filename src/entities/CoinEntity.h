#ifndef CG_COINENTITY_H
#define CG_COINENTITY_H

#include "Entity.h"

class CoinEntity : public Entity {
public:
    explicit CoinEntity(Model *model);

    ~CoinEntity() override;

    void update(float deltaTime) override;

    void render(const Camera &camera);

    float getDistanceToPlayer() const;

    void setDistanceToPlayer(float distanceToPlayer);

private:
    Vector3f pos;
    float rotation = 0;
    float speed;
    float distanceToPlayer = 0;

    float rndFloat(float min, float max);
};


#endif //CG_COINENTITY_H
