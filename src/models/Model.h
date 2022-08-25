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
    explicit Model();

    virtual ~Model();

    virtual void render() const = 0;

    AABB getBoundingBox() const;

protected:
    std::vector<Mesh> meshes;
    AABB boundingBox;

    void setBoundingBox();

private:
    void drawBoundingBox() const;
};


#endif //CG_MODEL_H
