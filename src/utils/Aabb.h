//
//  Aabb.hpp
//  CGXcode
//
//  Created by Philipp Lensing on 02.11.16.
//  Copyright © 2016 Philipp Lensing. All rights reserved.
//

#ifndef Aabb_hpp
#define Aabb_hpp

#include <cstdio>
#include "../maths/Matrix.h"
#include "../maths/Vector3f.h"
#include "../maths/Matrix.h"

class AABB {
public:
    Vector3f Min;
    Vector3f Max;

    AABB();

    AABB(const Vector3f &min, const Vector3f &max);

    AABB(float minX, float minY, float minZ, float maxX, float maxY, float maxZ);

    Vector3f size() const;

    AABB transform(const Matrix &m) const;

    AABB merge(const AABB &a, const AABB &b) const;

    AABB &merge(const AABB &a);

    Vector3f center() const;

    void corners(Vector3f c[8]) const;

    void fromPoints(const Vector3f *Points, unsigned int PointCount);

    static const AABB &unitBox();

protected:
    static AABB UnitBox;
};


#endif /* Aabb_hpp */
