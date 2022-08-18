//
// Created by Patrick on 11.08.2022.
//

#ifndef CG_GUNENTITY_H
#define CG_GUNENTITY_H


#include "Entity.h"
#include "BulletEntity.h"


class GunEntity : public Entity {
public:
    explicit GunEntity(Model *gunModel, GLFWwindow &window);

    ~GunEntity() override;

    void update(float deltaTime) override;

    void render(const Camera &camera);

    void setTargets(std::vector<Entity*> *v);

private:
    GLFWwindow &window;

    bool readyToFire = true;

    std::vector<Entity*> *targets;
    Vector3f weaponOffset;

    void shoot(const Camera &camera);
};


#endif //CG_GUNENTITY_H
