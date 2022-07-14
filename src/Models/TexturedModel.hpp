#ifndef TexturedModel_hpp
#define TexturedModel_hpp

#include "RawModel.hpp"
#include "../Textures/ModelTexture.hpp"

class TexturedModel {
private:
    RawModel rawModel;
    ModelTexture texture;
public:
    TexturedModel();

    TexturedModel(RawModel model, ModelTexture texture);

    virtual ~TexturedModel();

    RawModel getRawModel();

    ModelTexture getTexture();
};

#endif