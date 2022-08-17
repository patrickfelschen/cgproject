//
//  Aabb.cpp
//  CGXcode
//
//  Created by Philipp Lensing on 02.11.16.
//  Copyright © 2016 Philipp Lensing. All rights reserved.
//

#include "Aabb.h"

AABB AABB::UnitBox(Vector3f(-1, -1, -1), Vector3f(1, 1, 1));

AABB::AABB() {

}

AABB::AABB(const Vector3f &min, const Vector3f &max) : Min(min), Max(max) {

}

AABB::AABB(float minX, float minY, float minZ, float maxX, float maxY, float maxZ) : Min(minX, minY, minZ),
                                                                                     Max(maxX, maxY, maxZ) {

}

Vector3f AABB::size() const {
    return Max - Min;
}

AABB AABB::transform(const Matrix &m) const {
    Vector3f c[8];
    corners(c);
    for (int i = 0; i < 8; ++i)
        c[i] = m * c[i];
    AABB r;
    r.fromPoints(c, 8);
    return r;
}

AABB AABB::merge(const AABB &a, const AABB &b) const {
    AABB r;

    r.Min.x = a.Min.x < b.Min.x ? a.Min.x : b.Min.x;
    r.Min.y = a.Min.y < b.Min.y ? a.Min.y : b.Min.y;
    r.Min.z = a.Min.z < b.Min.z ? a.Min.z : b.Min.z;

    r.Max.x = a.Max.x > b.Max.x ? a.Max.x : b.Max.x;
    r.Max.y = a.Max.y > b.Max.y ? a.Max.y : b.Max.y;
    r.Max.z = a.Max.z > b.Max.z ? a.Max.z : b.Max.z;

    return r;
}

AABB &AABB::merge(const AABB &a) {
    Min.x = a.Min.x < Min.x ? a.Min.x : Min.x;
    Min.y = a.Min.y < Min.y ? a.Min.y : Min.y;
    Min.z = a.Min.z < Min.z ? a.Min.z : Min.z;

    Max.x = a.Max.x > Max.x ? a.Max.x : Max.x;
    Max.y = a.Max.y > Max.y ? a.Max.y : Max.y;
    Max.z = a.Max.z > Max.z ? a.Max.z : Max.z;

    return *this;
}

void AABB::corners(Vector3f c[8]) const {
    c[0].x = Min.x;
    c[0].y = Min.y;
    c[0].z = Min.z;
    c[1].x = Max.x;
    c[1].y = Min.y;
    c[1].z = Min.z;
    c[2].x = Max.x;
    c[2].y = Max.y;
    c[2].z = Min.z;
    c[3].x = Max.x;
    c[3].y = Min.y;
    c[3].z = Min.z;

    c[4].x = Min.x;
    c[4].y = Min.y;
    c[4].z = Max.z;
    c[5].x = Max.x;
    c[5].y = Min.y;
    c[5].z = Max.z;
    c[6].x = Max.x;
    c[6].y = Max.y;
    c[6].z = Max.z;
    c[7].x = Max.x;
    c[7].y = Min.y;
    c[7].z = Max.z;
}

void AABB::fromPoints(const Vector3f *Points, unsigned int PointCount) {
    Max = Vector3f(-1e20f, -1e20f, -1e20f);
    Min = Vector3f(1e20f, 1e20f, 1e20f);

    for (unsigned int i = 0; i < PointCount; ++i) {
        if (Min.x > Points[i].x) Min.x = Points[i].x;
        if (Min.y > Points[i].y) Min.y = Points[i].y;
        if (Min.z > Points[i].z) Min.z = Points[i].z;
        if (Max.x < Points[i].x) Max.x = Points[i].x;
        if (Max.y < Points[i].y) Max.y = Points[i].y;
        if (Max.z < Points[i].z) Max.z = Points[i].z;
    }

}

Vector3f AABB::center() const {
    return (Max + Min) * 0.5f;
}

const AABB &AABB::unitBox() {
    return UnitBox;
}

