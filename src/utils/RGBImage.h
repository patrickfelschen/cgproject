#ifndef CG_RGBIMAGE_H
#define CG_RGBIMAGE_H


#include <cassert>
#include <vector>
#include "Color.h"
#include "../maths/Vector3f.h"

class RGBImage {
public:
    RGBImage(unsigned int width, unsigned height);

    ~RGBImage();

    Color getPixelColor(unsigned int x, unsigned int y) const;

    void setPixelColor(unsigned int x, unsigned int y, const Color &c);

    static unsigned char convertColorChannel(float f);

protected:
    std::vector<Color> imageData;
    unsigned int height;
    unsigned int width;
};

#endif //CG_RGBIMAGE_H
