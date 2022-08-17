#include "RGBImage.h"

RGBImage::RGBImage() : width(0), height(0) {

}

RGBImage::RGBImage(unsigned int width, unsigned height) : width(width), height(height) {
    data = std::vector<Color>(width * height, Color());
}

RGBImage::~RGBImage() = default;

void RGBImage::setPixelColor(unsigned int x, unsigned int y, const Color &c) {
    if (x >= width || y >= height) return;
    data[x + width * y] = c;
}

Color RGBImage::getPixelColor(unsigned int x, unsigned int y) const {
    if (x >= width || y >= height) return {};
    return data[x + width * y];
}

unsigned char RGBImage::convertColorChannel(float v) {
    //https://stackoverflow.com/a/26298699
    if (v < 0) return 0;
    if (v > 1.0f) return 255;
    return (unsigned char) (v * 255);
}

unsigned int RGBImage::getHeight() const {
    return height;
}

unsigned int RGBImage::getWidth() const {
    return width;
}

const std::vector<Color> &RGBImage::getData() const {
    return data;
}
