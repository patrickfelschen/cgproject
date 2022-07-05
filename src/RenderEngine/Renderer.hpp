//
//  Renderer.hpp
//
//  Created by Patrick Felschen on 12.05.22.
//

#ifndef Renderer_hpp
#define Renderer_hpp

#include <stdio.h>
#include "../GLincludes.hpp"
#include "../Models/RawModel.hpp"
#include "../Models/TexturedModel.hpp" 
#include "../Entities/Entitiy.hpp"
#include "../Shaders/StaticShader.hpp"
#include "../Toolbox/Maths.hpp"

class Renderer {
private:
	static const float FOV;
	static const float NEAR_PLANE;
	static const float FAR_PLANE;
	Matrix projectionMatrix;
	float width, height;
	void createProjectionMatrix();
public:
	Renderer(float width, float height, StaticShader shader);
	virtual ~Renderer();
	void prepare();
	void render(Entity entity, StaticShader shader);
};

#endif /* Renderer_hpp */
