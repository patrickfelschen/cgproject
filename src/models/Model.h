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

    virtual void update(float deltaTime);

    virtual void render(const Camera &camera);

    void translate(const Vector3f &v);

    void scale(const float &v);

    void rotateX(float angle);

    void rotateY(float angle);

    void rotateZ(float angle);

protected:
    Shader *shader;
    std::vector<Mesh> meshes;
    AABB boundingBox;

    void setBoundingBox();

private:
    Matrix translation;
    Matrix rotationX;
    Matrix rotationY;
    Matrix rotationZ;
    Matrix scaling;

    void drawBoundingBox();
};


#endif //CG_MODEL_H
