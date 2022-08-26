#include <cassert>
#include "Color.h"

Color::Color() : r(0), g(0), b(0), a(1.0f) {
}

Color::Color(float rgba) : r(rgba), g(rgba), b(rgba), a(rgba) {
    assert(rgba >= 0.0f || rgba <= 1.0f);
}

Color::Color(const aiColor4D &aiColor) : r(aiColor.r), g(aiColor.g), b(aiColor.b), a(aiColor.a) {

}

Color::Color(float r, float g, float b) : r(r), g(g), b(b), a(1.0f) {
    assert(r >= 0.0f || r <= 1.0f);
    assert(g >= 0.0f || g <= 1.0f);
    assert(b >= 0.0f || b <= 1.0f);
}

Color::Color(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) {
    assert(r >= 0.0f || r <= 1.0f);
    assert(g >= 0.0f || g <= 1.0f);
    assert(b >= 0.0f || b <= 1.0f);
    assert(a >= 0.0f || a <= 1.0f);
}

Color::Color(unsigned char r, unsigned char g, unsigned char b) {
    this->r = (float) (r / 255.0);
    this->g = (float) (g / 255.0);
    this->b = (float) (b / 255.0);
    this->a = 1.0f;
}

Color::Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
    this->r = (float) (r / 255.0);
    this->g = (float) (g / 255.0);
    this->b = (float) (b / 255.0);
    this->a = (float) (a / 255.0);
}

Color Color::operator*(const Color &c) const {
    return {r * c.r, g * c.g, b * c.b, a * c.a};
}

Color Color::operator*(const float factor) const {
    return {r * factor, g * factor, b * factor, a * factor};
}

Color Color::operator+(const Color &c) const {
    return {r + c.r, g + c.g, b + c.b, a + c.a};
}

Color &Color::operator+=(const Color &c) {
    r += c.r;
    g += c.g;
    b += c.b;
    a += c.a;
    return *this;
}




