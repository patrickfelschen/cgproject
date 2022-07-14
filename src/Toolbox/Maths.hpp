#ifndef Maths_hpp
#define Maths_hpp

#define _USE_MATH_DEFINES

#include "../Utils/Matrix.h"
#include "../Entities/Camera.hpp"
#include <math.h>

class Maths {
public:
    Maths();

    ~Maths();

    static Matrix
    createTransformationMatrix(const Vector &translation, const float &rx, const float &ry, const float &rz,
                               const float &scale);

    static Matrix createViewMatrix(Camera camera);

    static float toRadians(const float &value);

private:

};

#endif