//
//  RawModel.cpp
//
//  Created by Patrick Felschen on 12.05.22.
//

#include "RawModel.hpp"

RawModel::RawModel() {}

RawModel::RawModel(GLuint vaoID, unsigned long vertexCount) {
    this->vaoID = vaoID;
    this->vertexCount = vertexCount;
}

RawModel::~RawModel() {
}

GLuint RawModel::getVaoID() {
    return this->vaoID;
}

void RawModel::setVaoID(GLuint vaoID) {
    this->vaoID = vaoID;
}

unsigned long RawModel::getVertexCount() {
    return this->vertexCount;
}

void RawModel::setVertexCount(unsigned long vertexCount) {
    this->vertexCount = vertexCount;
}
