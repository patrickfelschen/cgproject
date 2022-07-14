#ifndef ModelTexture_hpp
#define ModelTexture_hpp

#include "../GLincludes.hpp"

class ModelTexture {
private:
    GLuint textureID;
public:
    ModelTexture();

    ModelTexture(GLuint textureID);

    virtual ~ModelTexture();

    GLuint getID();
};

#endif