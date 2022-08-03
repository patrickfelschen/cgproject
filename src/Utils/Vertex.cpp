//
// Created by Patrick on 03.08.2022.
//

#include "Vertex.h"

Vertex::Vertex(
        const Vector3f &pos,
        const Vector2f &texCoords,
        const Vector3f &normal
) : pos(pos), texCoords(texCoords), normal(normal) {}
