#include "Entitiy.hpp"

Entity::Entity() {
}

Entity::Entity(TexturedModel* model, Vector position, float rotX, float rotY, float rotZ, float scale)
{
	this->model = model;
	this->position = position;
	this->rotX = rotX;
	this->rotY = rotY;
	this->rotZ = rotZ;
	this->scale = scale;
}

Entity::~Entity()
{
}

TexturedModel* Entity::getModel()
{
	return this->model;
}

Vector Entity::getPosition()
{
	return this->position;
}

float Entity::getRotX()
{
	return this->rotX;
}

float Entity::getRotY()
{
	return this->rotY;
}

float Entity::getRotZ()
{
	return this->rotZ;
}

float Entity::getScale()
{
	return this->scale;
}

void Entity::setModel(TexturedModel* model)
{
	this->model = model;
}

void Entity::setPosition(Vector pos)
{
	this->position = pos;
}

void Entity::setRotX(float rotX)
{
	this->rotX = rotX;
}

void Entity::setRotY(float rotY)
{
	this->rotY = rotY;
}

void Entity::setRotZ(float rotZ)
{
	this->rotZ = rotZ;
}

void Entity::setScale(float scale)
{
	this->scale = scale;
}

void Entity::increasePosition(float dx, float dy, float dz)
{
	this->position.X += dx;
	this->position.Y += dy;
	this->position.Z += dz;

}

void Entity::increaseRotation(float dx, float dy, float dz)
{
	this->rotX += dx;
	this->rotY += dy;
	this->rotZ += dz;
}


