#include "ModelTexture.hpp"

ModelTexture::ModelTexture() {}

ModelTexture::ModelTexture(GLuint textureID) {
    this->textureID = textureID;
}

ModelTexture::~ModelTexture() {
}

GLuint ModelTexture::getID() {
    return this->textureID;
}
