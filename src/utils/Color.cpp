#include "Color.h"

Color::Color() : r(0), g(0), b(0) {
}

Color::Color(float r, float g, float b) : r(r), g(g), b(b) {
}

Color Color::operator*(const Color &c) const {
    return {r * c.r, g * c.g, b * c.b};
}

Color Color::operator*(const float factor) const {
    return {r * factor, g * factor, b * factor};
}

Color Color::operator+(const Color &c) const {
    return {r + c.r, g + c.g, b + c.b};
}

Color &Color::operator+=(const Color &c) {
    r += c.r;
    g += c.g;
    b += c.b;

    return *this;
}