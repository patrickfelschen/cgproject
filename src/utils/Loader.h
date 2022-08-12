//
// Created by Patrick on 01.08.2022.
//

#ifndef CG_LOADER_H
#define CG_LOADER_H

#include <string>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include "GL/glew.h"
#include "RGBImage.h"
#include "FreeImage.h"
#include "RGBImage.h"
#include <cassert>
#include <vector>

class Loader {
public:
    static void readImageFile(const char *filePath, RGBImage &outImage);

    static void readShaderFile(const char *filePath, std::string &outFile);
};


#endif //CG_LOADER_H
