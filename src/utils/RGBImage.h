#ifndef CG_RGBIMAGE_H
#define CG_RGBIMAGE_H


#include <cassert>
#include <vector>
#include "Color.h"
#include "../maths/Vector3f.h"
#include "GL/glew.h"

class RGBImage {
public:
    RGBImage();

    RGBImage(unsigned int width, unsigned height, GLenum format);

    ~RGBImage();

    Color getPixelColor(unsigned int x, unsigned int y) const;

    void setPixelColor(unsigned int x, unsigned int y, const Color &c);

    static unsigned char convertColorChannel(float f);

    unsigned int getHeight() const;

    unsigned int getWidth() const;

    const std::vector<Color> &getData() const;

    GLenum getFormat() const;

private:
    std::vector<Color> data;
    unsigned int height;
    unsigned int width;
    GLenum format;
};

#endif //CG_RGBIMAGE_H
