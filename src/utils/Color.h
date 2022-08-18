#ifndef CG_COLOR_H
#define CG_COLOR_H

#include "assimp/types.h"

class Color {
public:
    float r;
    float g;
    float b;
    float a;

    Color();

    explicit Color(const aiColor3D &aiColor);

    Color(float r, float g, float b, float a);

    Color(float r, float g, float b);

    Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a);

    Color(unsigned char r, unsigned char g, unsigned char b);

    Color operator*(const Color &c) const;

    Color operator*(float factor) const;

    Color operator+(const Color &c) const;

    Color &operator+=(const Color &c);
};

#endif //CG_COLOR_H
