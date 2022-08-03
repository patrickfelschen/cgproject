//
// Created by Patrick on 01.08.2022.
//

#ifndef CG_RENDERABLE_H
#define CG_RENDERABLE_H

#include "../utils/Camera.h"

class Renderable {
public:
    virtual ~Renderable() = default;

    virtual void update(float deltaTime) = 0;

    virtual void render(const Camera &camera) = 0;
};

#endif //CG_RENDERABLE_H
