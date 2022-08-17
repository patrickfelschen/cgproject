//
// Created by Patrick on 12.08.2022.
//

#ifndef CG_TERRAIN_H
#define CG_TERRAIN_H


#include "../shaders/Shader.h"
#include "../models/Model.h"

class Terrain : public Model {
public:
    explicit Terrain(Shader *shader);

    ~Terrain() override = default;

    void update(float deltaTime) override;

    void render(const Camera &camera) override;

private:
    float width;
    float height;
    float depth;

    void generate();
};


#endif //CG_TERRAIN_H
