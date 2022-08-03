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
    Vector3f pos;
    Vector2f texCoords;
    Vector3f normal;

    Vertex(const Vector3f &pos, const Vector2f &texCoords, const Vector3f &normal);
};


#endif //CG_VERTEX_H
