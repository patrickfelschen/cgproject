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
#include "../Toolbox/TextureLoader.hpp"
#include "../Utils/Mesh.h"

class Loader {
private:
    std::vector<GLuint> vaos;
    std::vector<GLuint> vbos;
    std::vector<GLuint> textures;

    int createVAO();

    void bindIndicesBuffer(const std::vector<unsigned int> &indices);

    void storeVerticesInAttributeList(const std::vector<Vertex> &vertices);

    void unbindVAO();

public:
    Loader();

    virtual ~Loader();

    void cleanUp();

    GLuint loadTexture(const std::string &file);

    RawModel loadToVAO(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &indices);

};

#endif /* Loader_hpp */
