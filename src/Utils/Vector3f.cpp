#include "Vector3f.h"
#include <assert.h>
#include <math.h>

#define EPSILON 1e-5

Vector3f::Vector3f(float x, float y, float z) {
    this->X = x;
    this->Y = y;
    this->Z = z;
}

Vector3f::Vector3f() {
    // Nichts
}

float Vector3f::dot(const Vector3f &v) const {
    return
            this->X * v.X +
            this->Y * v.Y +
            this->Z * v.Z;
}

Vector3f Vector3f::cross(const Vector3f &v) const {
    return Vector3f(
            this->Y * v.Z - this->Z * v.Y,
            this->Z * v.X - this->X * v.Z,
            this->X * v.Y - this->Y * v.X
    );
}


Vector3f Vector3f::operator+(const Vector3f &v) const {
    return Vector3f(
            this->X + v.X,
            this->Y + v.Y,
            this->Z + v.Z
    );
}

Vector3f Vector3f::operator-(const Vector3f &v) const {
    return Vector3f(
            this->X - v.X,
            this->Y - v.Y,
            this->Z - v.Z
    );
}

Vector3f Vector3f::operator*(float c) const {
    return Vector3f(
            this->X * c,
            this->Y * c,
            this->Z * c
    );
}

Vector3f Vector3f::operator-() const {
    return *this * -1;
}

Vector3f &Vector3f::operator+=(const Vector3f &v) {
    this->X = this->X + v.X;
    this->Y = this->Y + v.Y;
    this->Z = this->Z + v.Z;

    return *this;
}

Vector3f &Vector3f::normalize() {
    float tmp = 1 / this->length();

    this->X = X * tmp;
    this->Y = Y * tmp;
    this->Z = Z * tmp;

    return *this;
}

float Vector3f::length() const {
    return sqrtf(this->lengthSquared());
}

float Vector3f::lengthSquared() const {
    return powf(this->X, 2) + powf(this->Y, 2) + powf(this->Z, 2);
}

Vector3f Vector3f::reflection(const Vector3f &normal) const {
    return *this - normal * (2 * this->dot(normal));
}

