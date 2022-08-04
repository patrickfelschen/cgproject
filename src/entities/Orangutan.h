//
// Created by Patrick on 04.08.2022.
//

#ifndef CG_ORANGUTAN_H
#define CG_ORANGUTAN_H


#include "Entity.h"

class Orangutan : public Entity {
public:
    Orangutan(Model *model);

    ~Orangutan() override;

    void update(float deltaTime) override;
};


#endif //CG_ORANGUTAN_H
