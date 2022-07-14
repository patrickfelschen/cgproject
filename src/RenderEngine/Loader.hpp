//
//  Loader.hpp
//
//  Created by Patrick Felschen on 12.05.22.
//

#ifndef Loader_hpp
#define Loader_hpp

#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>
#include <cassert>
#include "FreeImage.h"
#include "../GLincludes.hpp"
#include "../Models/RawModel.hpp"
#include "../Utils/rgbimage.h"
#include "../Utils/color.h"
#include "../Toolbox/TextureLoader.hpp"

class Loader {
private:
    std::vector<GLuint> vaos;
    std::vector<GLuint> vbos;
    std::vector<GLuint> textures;

    int createVAO();

    void storeDataInAttributeList(GLuint attributeNumber, unsigned int coordinateSize, std::vector<float> data);

    void bindIndicesBuffer(std::vector<int> indices);

    void unbindVAO();

public:
    Loader();

    virtual ~Loader();

    RawModel loadToVAO(std::vector<float> positions, std::vector<float> textureCoords, std::vector<int> indices);

    void cleanUp();

    GLuint loadTexture(std::string file);
};

#endif /* Loader_hpp */
