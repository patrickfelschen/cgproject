#include "Vector3f.h"

Vector3f::Vector3f(float x, float y, float z) : x(x), y(y), z(z) {}

Vector3f::Vector3f() : x(0), y(0), z(0) {}

float Vector3f::dot(const Vector3f &v) const {
    return
            this->x * v.x +
            this->y * v.y +
            this->z * v.z;
}

Vector3f Vector3f::cross(const Vector3f &v) const {
    return {
            this->y * v.z - this->z * v.y,
            this->z * v.x - this->x * v.z,
            this->x * v.y - this->y * v.x
    };
}


Vector3f Vector3f::operator+(const Vector3f &v) const {
    return {
            this->x + v.x,
            this->y + v.y,
            this->z + v.z
    };
}

Vector3f Vector3f::operator-(const Vector3f &v) const {
    return {
            this->x - v.x,
            this->y - v.y,
            this->z - v.z
    };
}

Vector3f Vector3f::operator*(float c) const {
    return {
            this->x * c,
            this->y * c,
            this->z * c
    };
}

Vector3f Vector3f::operator-() const {
    return *this * -1;
}

Vector3f &Vector3f::operator+=(const Vector3f &v) {
    this->x = this->x + v.x;
    this->y = this->y + v.y;
    this->z = this->z + v.z;

    return *this;
}

Vector3f &Vector3f::operator-=(const Vector3f &v) {
    this->x = this->x - v.x;
    this->y = this->y - v.y;
    this->z = this->z - v.z;

    return *this;
}

Vector3f &Vector3f::operator*=(float c) {
    this->x = this->x * c;
    this->y = this->y * c;
    this->z = this->z * c;

    return *this;
}

Vector3f &Vector3f::normalize() {
    float tmp = 1 / this->length();

    this->x = x * tmp;
    this->y = y * tmp;
    this->z = z * tmp;

    return *this;
}

float Vector3f::length() const {
    return sqrtf(this->lengthSquared());
}

float Vector3f::lengthSquared() const {
    return powf(this->x, 2) + powf(this->y, 2) + powf(this->z, 2);
}

Vector3f Vector3f::reflection(const Vector3f &normal) const {
    return *this - normal * (2 * this->dot(normal));
}

void Vector3f::print() {
    std::cout << x << " ";
    std::cout << y << " ";
    std::cout << z << std::endl;
}





