#include "Color.h"

Color::Color() : r(0), g(0), b(0), a(0) {
}

Color::Color(float rgba) : r(rgba), g(rgba), b(rgba), a(rgba) {
}

Color::Color(const aiColor3D &aiColor) : r(aiColor.r), g(aiColor.g), b(aiColor.b) {

}

Color::Color(float r, float g, float b) : r(r), g(g), b(b), a(1.0f) {
}

Color::Color(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) {
}

Color::Color(unsigned char r, unsigned char g, unsigned char b) {
    this->r = (float) (r / 255.0);
    this->g = (float) (g / 255.0);
    this->b = (float) (b / 255.0);
}

Color::Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
    this->r = (float) (r / 255.0);
    this->g = (float) (g / 255.0);
    this->b = (float) (b / 255.0);
    this->a = (float) (a / 255.0);
}

Color Color::operator*(const Color &c) const {
    return {r * c.r, g * c.g, b * c.b, a * c.b};
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




