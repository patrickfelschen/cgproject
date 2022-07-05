#ifndef Entity_hpp
#define Entity_hpp

#include "../Models/TexturedModel.hpp"
#include "../util/vector.h"

class Entity {
private:
	TexturedModel* model;
	Vector position;
	float rotX, rotY, rotZ;
	float scale;
public:
	Entity();
	Entity(TexturedModel* model, Vector position, float rotX, float rotY, float rotZ, float scale);
	~Entity();
	TexturedModel* getModel();
	Vector getPosition();
	float getRotX();
	float getRotY();
	float getRotZ();
	float getScale();
	void setModel(TexturedModel* model);
	void setPosition(Vector pos);
	void setRotX(float rotX);
	void setRotY(float rotY);
	void setRotZ(float rotZ);
	void setScale(float scale);
	void increasePosition(float dx, float dy, float dz);
	void increaseRotation(float dx, float dy, float dz);
};

#endif