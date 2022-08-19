//
// Created by Patrick on 04.08.2022.
//

#ifndef CG_MODEL_H
#define CG_MODEL_H


#include "../maths/Matrix.h"
#include "../utils/Camera.h"
#include "../shaders/Shader.h"
#include "../utils/Mesh.h"
#include "../utils/Aabb.h"

class Model {
public:
    explicit Model(Shader *shader);

    virtual ~Model();

    virtual void update(float deltaTime) const;

    virtual void render(const Camera &camera, const Matrix &transform) const;

    AABB getBoundingBox() const;

protected:
    Shader *shader;
    std::vector<Mesh> meshes;
    AABB boundingBox;

    void setBoundingBox();

private:
    Matrix transformation;

    void drawBoundingBox() const;
};


#endif //CG_MODEL_H
