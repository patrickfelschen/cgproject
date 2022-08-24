//
// Created by Patrick on 03.08.2022.
//

#ifndef CG_VERTEX_H
#define CG_VERTEX_H


#include <vector>
#include "../maths/Vector3f.h"
#include "../maths/Vector2f.h"

class Vertex {
public:
    Vertex();

    virtual ~Vertex();

    Vector3f pos;
    Vector3f normal;
    Vector2f texCoord0;
    Vector2f texCoord1;

    Vertex(const Vector3f &pos, const Vector3f &normal, const Vector2f &texCoord0, const Vector2f &texCoord1);
};


#endif //CG_VERTEX_H
