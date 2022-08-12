#include "RGBImage.h"

RGBImage::RGBImage(unsigned int width, unsigned height) : width(width), height(height) {
    imageData = std::vector<Color>(width * height, Color());
}

RGBImage::~RGBImage() = default;

void RGBImage::setPixelColor(unsigned int x, unsigned int y, const Color &c) {
    if (x >= width || y >= height) return;
    imageData[x + width * y] = c;
}

Color RGBImage::getPixelColor(unsigned int x, unsigned int y) const {
    if (x >= width || y >= height) return {};
    return imageData[x + width * y];
}

unsigned char RGBImage::convertColorChannel(float v) {
    //https://stackoverflow.com/a/26298699
    if (v < 0) return 0;
    if (v > 1.0f) return 255;
    return (unsigned char) (v * 255);
}
