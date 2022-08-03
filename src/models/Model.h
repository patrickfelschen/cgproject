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
#include "../textures/Texture.h"

class Model : public Renderable {
public:
    explicit Model(const Shader &shader, const Texture &texture);

    ~Model() override = default;

    void update(float deltaTime) override;

    void render(const Camera &camera) override;

    void setPosition(const Vector3f& v);
    void setScale(const float& v);
    void setRotation(const Vector3f& v, const float& a);

private:
    GLuint VBO = 0;
    GLuint VAO = 0;
    GLuint EBO = 0;

    Shader shader;
    Texture texture;

    Matrix transform;
};


#endif //CG_MODEL_H
