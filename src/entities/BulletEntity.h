#ifndef CG_BULLETENTITY_H
#define CG_BULLETENTITY_H


#include "Entity.h"

class BulletEntity : public Entity {
public:
    explicit BulletEntity(Model *model, Vector3f startPos, Vector3f dir);

    ~BulletEntity() override;

    void update(float deltaTime) override;

    void render(const Camera &camera);

    void setYaw(float yaw);

    void setPitch(float pitch);

private:
    Vector3f pos;
    Vector3f dir;
    float yaw;
    float pitch;
    float speed;
};


#endif //CG_BULLETENTITY_H
