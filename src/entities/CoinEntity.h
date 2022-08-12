#ifndef CG_COINENTITY_H
#define CG_COINENTITY_H

#include "Entity.h"

class CoinEntity : public Entity {
public:
    explicit CoinEntity(Model *model);

    ~CoinEntity() override;

    void update(float deltaTime) override;

    void render(const Camera &camera);
private:
    float rndFloat(float min, float max);
    Vector3f pos;
    float rotation = 0;
    float speed;
};


#endif //CG_COINENTITY_H
