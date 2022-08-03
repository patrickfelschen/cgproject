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

}

void RGBImage::setPixelColor(unsigned int x, unsigned int y, const Color &c) {
    if (x >= m_Width || y >= m_Height)
        return;

    m_Image[x + m_Width * y] = c;
}

const Color &RGBImage::getPixelColor(unsigned int x, unsigned int y) const {
    //https://softwareengineering.stackexchange.com/a/212813

    if (x >= m_Width || y >= m_Height)
        return Color();

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

RGBImage& RGBImage::SobelFilter(RGBImage& dst, const RGBImage& src, float factor)
{
    assert(dst.m_Height == src.m_Height, "height not equal");
    assert(dst.m_Width == src.m_Width, "width not equal");
    int K[9] = { 1, 0, -1, 2, 0, -2, 1, 0, -1 };

    // Formel f�r Sobel Filter anwenden (Bildfilter zur Kantenhervorhebung)
    for (unsigned int x = 0; x < src.width(); x++)
    {
        for (unsigned int y = 0; y < src.height(); y++)
        {
            Color U;
            Color V;
            for (unsigned int i = 0; i <= 2; i++)
            {
                for (unsigned int j = 0; j <= 2; j++)
                {
                    U += src.getPixelColor(x - i - 1, y - j - 1) * K[i + 3 * j];
                    V += src.getPixelColor(x - i - 1, y - j - 1) * K[j + 3 * i];
                }
            }
            Color S;
            S.R = sqrt(pow(U.R, 2) + pow(V.R, 2));
            S.G = sqrt(pow(U.G, 2) + pow(V.G, 2));
            S.B = sqrt(pow(U.B, 2) + pow(V.B, 2));
            S = S * factor;

            dst.setPixelColor(x, y, S);
        }
    }
    return dst;
}


bool RGBImage::saveToDisk(const char *Filename) {

    // https://stackoverflow.com/a/30423762
    // http://de.wikipedia.org/wiki/Windows_Bitmap

    typedef struct                      /**** BMP file header structure ****/
    {
        unsigned int bfSize;            /* Size of file */
        unsigned int bfReserved;        /* Reserved */
        unsigned int bfOffBits;         /* Offset to bitmap data */
    } BITMAPFILEHEADER;

    typedef struct                       /**** BMP file info structure ****/
    {
        unsigned int biSize;            /* Size of info header */
        int biWidth;                    /* Width of image */
        int biHeight;                   /* Height of image */
        unsigned short biPlanes;        /* Number of color planes */
        unsigned short biBitCount;      /* Number of bits per pixel */
        unsigned int biCompression;     /* Type of compression to use */
        unsigned int biSizeImage;       /* Size of image data */
        int biXPelsPerMeter;            /* X pixels per meter */
        int biYPelsPerMeter;            /* Y pixels per meter */
        unsigned int biClrUsed;         /* Number of colors used */
        unsigned int biClrImportant;    /* Number of important colors */
    } BITMAPINFOHEADER;

    BITMAPFILEHEADER bfh;
    BITMAPINFOHEADER bih;

    /* Magic number for file.
     * It does not fit in the header structure due to alignment requirements.
     */
    unsigned short bfType = 0x4d42;

    bfh.bfReserved = 0;
    bfh.bfSize = 2 + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + m_Width * m_Height * 3;
    bfh.bfOffBits = 0x36;

    bih.biSize = sizeof(BITMAPINFOHEADER);
    bih.biWidth = m_Width;
    bih.biHeight = m_Height;
    bih.biPlanes = 1;
    bih.biBitCount = 24;
    bih.biCompression = 0;
    bih.biSizeImage = 0;
    bih.biXPelsPerMeter = 0;
    bih.biYPelsPerMeter = 0;
    bih.biClrUsed = 0;
    bih.biClrImportant = 0;

    FILE *pFile = fopen(Filename, "wb");

    /*Write headers*/
    fwrite(&bfType, 1, sizeof(bfType), pFile);
    fwrite(&bfh, 1, sizeof(bfh), pFile);
    fwrite(&bih, 1, sizeof(bih), pFile);

    /*Write bitmap*/
    for (int y = bih.biHeight - 1; y >= 0; y--) /*Scanline loop backwards*/
    {
        for (int x = 0; x < bih.biWidth; x++) /*Column loop forwards*/
        {
            /*compute some pixel values*/
            unsigned char r = convertColorChannel(getPixelColor(x,y).R);
            unsigned char g = convertColorChannel(getPixelColor(x,y).G);
            unsigned char b = convertColorChannel(getPixelColor(x,y).B);

            fwrite(&b, sizeof(b), 1, pFile);
            fwrite(&g, sizeof(g), 1, pFile);
            fwrite(&r, sizeof(r), 1, pFile);
        }
    }

    fclose(pFile);
    return true;
}
