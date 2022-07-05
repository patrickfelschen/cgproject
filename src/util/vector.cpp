#include "vector.h"
#include <assert.h>
#include <math.h>

#define EPSILON 1e-5

Vector::Vector(float x, float y, float z) {
    this->X = x;
    this->Y = y;
    this->Z = z;
}

Vector::Vector() {
    // Nichts
}

float Vector::dot(const Vector &v) const {
    return
            this->X * v.X +
            this->Y * v.Y +
            this->Z * v.Z;
}

Vector Vector::cross(const Vector &v) const {
    return Vector(
            this->Y * v.Z - this->Z * v.Y,
            this->Z * v.X - this->X * v.Z,
            this->X * v.Y - this->Y * v.X
    );
}


Vector Vector::operator+(const Vector &v) const {
    return Vector(
            this->X + v.X,
            this->Y + v.Y,
            this->Z + v.Z
    );
}

Vector Vector::operator-(const Vector &v) const {
    return Vector(
            this->X - v.X,
            this->Y - v.Y,
            this->Z - v.Z
    );
}

Vector Vector::operator*(float c) const {
    return Vector(
            this->X * c,
            this->Y * c,
            this->Z * c
    );
}

Vector Vector::operator-() const {
    return *this * -1;
}

Vector &Vector::operator+=(const Vector &v) {
    this->X = this->X + v.X;
    this->Y = this->Y + v.Y;
    this->Z = this->Z + v.Z;

    return *this;
}

Vector &Vector::normalize() {
    float tmp = 1 / this->length();

    this->X = X * tmp;
    this->Y = Y * tmp;
    this->Z = Z * tmp;

    return *this;
}

float Vector::length() const {
    return sqrtf(this->lengthSquared());
}

float Vector::lengthSquared() const {
    return powf(this->X, 2) + powf(this->Y, 2) + powf(this->Z, 2);
}

Vector Vector::reflection(const Vector &normal) const {
    return *this - normal * (2 * this->dot(normal));
}

/***
 * Führt einen Kollisionstest zwischen einem Strahl und einem Dreieck durch.
 * @param d Richtung des Strahls
 * @param a Punkt des Dreiecks
 * @param b Punkt des Dreiecks
 * @param c Punkt des Dreiecks
 * @param s Fuer die bestimmung des Auftreffpunkts
 * @return true wenn sich Ebene und Strahl schneiden
 */
bool Vector::triangleIntersection(const Vector &d, const Vector &a, const Vector &b, const Vector &c, float &s) const {
    Vector ab = a - b;
    Vector bc = b - c;
    Vector n = ab.cross(bc);

    float dotnd = n.dot(d);

    if (fabs(dotnd) < EPSILON) return false;

    float scal = n.dot(c);
    s = (scal - n.dot(*this)) / dotnd;

    if (s < 0) return false;

    Vector dest = *this + (d * s);

    float abc = (a - b).cross(c - b).length() / 2;

    float abd = (a - dest).cross(b - dest).length() / 2;
    float acd = (a - dest).cross(c - dest).length() / 2;
    float bcd = (b - dest).cross(c - dest).length() / 2;

    if (abc + EPSILON >= abd + acd + bcd) return true;

    return false;
}

