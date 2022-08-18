#ifndef __SimpleRayTracer__Vector3f__
#define __SimpleRayTracer__Vector3f__

#include <iostream>
#include <cmath>

class Vector3f {
public:
    float x;
    float y;
    float z;

    Vector3f();

    Vector3f(float x, float y, float z);

    float dot(const Vector3f &v) const;

    Vector3f cross(const Vector3f &v) const;

    Vector3f operator+(const Vector3f &v) const;

    Vector3f operator-(const Vector3f &v) const;

    Vector3f &operator+=(const Vector3f &v);

    Vector3f &operator-=(const Vector3f &v);

    Vector3f operator*(float c) const;

    Vector3f &operator*=(float c);

    Vector3f operator-() const;

    Vector3f &normalize();

    float length() const;

    float lengthSquared() const;

    Vector3f reflection(const Vector3f &normal) const;

    void print() const;

};

#endif /* defined(__SimpleRayTracer__Vector3f__) */
