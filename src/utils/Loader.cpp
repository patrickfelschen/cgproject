//
// Created by Patrick on 01.08.2022.
// https://ogldev.org/www/tutorial04/tutorial04.html
//

#include "Loader.h"


/**
 *
 * @param filePath
 * @param outFile
 * @return
 */
void Loader::readShaderFile(const char *filePath, std::string &outFile) {
    std::ifstream f(filePath);
    if (f.is_open()) {
        std::string line;
        while (std::getline(f, line)) {
            outFile.append(line);
            outFile.append("\n");
        }
        f.close();
        std::cout << "LOADER::READSHADERFILE: " << filePath << std::endl;
        return;
    } else {
        std::cerr << "ERROR::LOADER::READSHADERFILE: " << filePath << std::endl;
        exit(EXIT_SUCCESS);
    }
}

void Loader::readImageFile(const char *filePath, RGBImage &outImage) {
    // Prüfe den Dateityp, ob es sich um eine BitMap handelt
    FREE_IMAGE_FORMAT imageFormat = FreeImage_GetFileType(filePath, 0);

    if (imageFormat == FIF_UNKNOWN) {
        imageFormat = FreeImage_GetFIFFromFilename(filePath);
    }
    if (imageFormat == FIF_UNKNOWN) {
        std::cout << "WARNING::LOADER::READIMAGEFILE: Unbekanntes Dateiformat! " << filePath << std::endl;
    }
    FIBITMAP *pBitMap = FreeImage_Load(imageFormat, filePath);
    if (pBitMap == nullptr) {
        std::cout << "ERROR::LOADER::READIMAGEFILE: Dateiformat kann nicht geoeffnet werden! " << filePath << std::endl;
        exit(EXIT_FAILURE);
    }

    //
    FreeImage_FlipVertical(pBitMap);

    FREE_IMAGE_TYPE type = FreeImage_GetImageType(pBitMap);
    assert(type == FIT_BITMAP);

    // Lese die Breite, Höhe und Bit pro Pixel der Datei aus.
    unsigned int width = FreeImage_GetWidth(pBitMap);
    unsigned int height = FreeImage_GetHeight(pBitMap);
    unsigned int bpp = FreeImage_GetBPP(pBitMap);
    assert(bpp == 16 || bpp == 24 || bpp == 32);

    // Speicherplatz für alle Pixel erstellen
    RGBImage image(width, height);

    // Speicherplatz für einzelnen Pixel erstellen
    RGBQUAD color;
    // Pixel Farbe auslesen und abspeichern
    for (unsigned int x = 0; x < width; x++) {
        for (unsigned int y = 0; y < width; y++) {
            FreeImage_GetPixelColor(pBitMap, x, y, &color);
            Color pixelColor = Color(color.rgbRed, color.rgbGreen, color.rgbBlue, color.rgbReserved);
            image.setPixelColor(x, y, pixelColor);
        }
    }

    // Speicherplatz freigeben
    FreeImage_Unload(pBitMap);

    std::cout << "LOADER::READIMAGEFILE: " << filePath << std::endl;
    outImage = image;
}