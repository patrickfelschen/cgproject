#ifndef CG_COLOR_H
#define CG_COLOR_H

class Color {
public:
    float r;
    float g;
    float b;

    Color();

    Color(float r, float g, float b);

    Color operator*(const Color &c) const;

    Color operator*(float factor) const;

    Color operator+(const Color &c) const;

    Color &operator+=(const Color &c);
};

#endif //CG_COLOR_H
