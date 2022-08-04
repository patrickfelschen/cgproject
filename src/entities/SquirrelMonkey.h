//
// Created by Patrick on 04.08.2022.
//

#ifndef CG_SQUIRRELMONKEY_H
#define CG_SQUIRRELMONKEY_H


#include "Entity.h"

class SquirrelMonkey : public Entity {
public:
    explicit SquirrelMonkey(Model *model);

    ~SquirrelMonkey() override;
};


#endif //CG_SQUIRRELMONKEY_H
