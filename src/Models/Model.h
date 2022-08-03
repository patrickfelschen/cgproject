//
// Created by Patrick on 01.08.2022.
//

#ifndef CG_MODEL_H
#define CG_MODEL_H

#include <iostream>
#include "GL/glew.h"
#include "../interfaces/Renderable.h"
#include "../maths/Vector3f.h"
#include "../utils/Loader.h"
#include "../shaders/Shader.h"

class Model : public Renderable {
public:
    explicit Model(const Shader &shader);

    ~Model() override = default;

    void update(float deltaTime) override;

    void render(const Camera &camera) override;

private:
    GLuint VBO = 0;
    GLuint VAO = 0;
    GLuint EBO = 0;

    Shader shader;
};


#endif //CG_MODEL_H
