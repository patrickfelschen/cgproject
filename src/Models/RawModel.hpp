//
//  RawModel.hpp
//
//  Created by Patrick Felschen on 12.05.22.
//

#ifndef RawModel_hpp
#define RawModel_hpp

#include <stdio.h>
#include "../GLincludes.hpp"

class RawModel {
private:
	GLuint vaoID;
	unsigned long vertexCount;
public:
	RawModel();
	RawModel(GLuint vaoID, unsigned long vertexCount);
	virtual ~RawModel();
	GLuint getVaoID();
	void setVaoID(GLuint vaoID);
	unsigned long getVertexCount();
	void setVertexCount(unsigned long vertexCount);
};

#endif /* RawModel_hpp */
