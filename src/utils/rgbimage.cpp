#include "rgbimage.h"
#include "color.h"
#include "assert.h"
#include "../maths/Vector3f.h"


RGBImage::RGBImage(unsigned int Width, unsigned Height) : m_Width(Width), m_Height(Height) {
    assert(Width > 0);
    assert(Height > 0);

    m_Image = new Color[Width * Height];
}

RGBImage::~RGBImage() {
    delete m_Image;
}

void RGBImage::setPixelColor(unsigned int x, unsigned int y, const Color &c) {
    if (x >= m_Width || y >= m_Height)
        return;

    m_Image[x + m_Width * y] = c;
}

const Color &RGBImage::getPixelColor(unsigned int x, unsigned int y) const {
    //https://softwareengineering.stackexchange.com/a/212813

    if (x >= m_Width || y >= m_Height)
        return m_Image[0];

    return m_Image[x + m_Width * y];
}

unsigned int RGBImage::width() const {
    return m_Width;
}

unsigned int RGBImage::height() const {
    return m_Height;
}

unsigned char RGBImage::convertColorChannel(float v) {
    //https://stackoverflow.com/a/26298699

    if (v < 0) {
        return 0;
    }

    if (v > 1.0f) {
        return 255;
    }

    return (unsigned char) (v * 255);
}
