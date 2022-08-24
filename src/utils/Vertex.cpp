//
// Created by Patrick on 03.08.2022.
//

#include "Vertex.h"


Vertex::Vertex() = default;

Vertex::~Vertex() = default;

Vertex::Vertex(const Vector3f &pos, const Vector3f &normal, const Vector2f &texCoord0, const Vector2f &texCoord1) : pos(
        pos), normal(normal), texCoord0(texCoord0), texCoord1(texCoord1) {}
