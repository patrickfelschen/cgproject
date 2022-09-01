#ifndef CG_AABB_H
#define CG_AABB_H

#include "../maths/Vector3f.h"
#include "../maths/Matrix.h"

struct Ray {
    Ray(Vector3f origin, Vector3f direction) {
        this->origin = origin;
        this->direction = direction;
    }
    Vector3f origin;
    Vector3f direction;
};

class AABB {
public:
    Vector3f Min;
    Vector3f Max;
    AABB();
    AABB(const Vector3f& min, const Vector3f& max);
    AABB(float minX, float minY, float minZ, float maxX, float maxY, float maxZ);
    Vector3f size() const;
    AABB transform(const Matrix& m) const;
    AABB merge(const AABB& a, const AABB& b) const;
    AABB& merge(const AABB& a);
    Vector3f center() const;
    void corners(Vector3f c[8]) const;
    void fromPoints(const Vector3f* Points, unsigned int PointCount);
    static const AABB& unitBox();
    bool intersection(const Ray &ray) const;
protected:
    static AABB UnitBox;
};


#endif //CG_AABB_H
