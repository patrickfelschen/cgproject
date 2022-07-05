#ifndef Camera_HPP
#define Camera_HPP

#include "../util/vector.h";
#include "../GLincludes.hpp"


class Camera {
private:
	Vector pos;
	float yaw, pitch, roll;
public:
	Camera();
	Camera(Vector pos);
	~Camera();
	Vector getPosition();
	float getYaw();
	float getPitch();
	float getRoll();
	void move(int key);
};

#endif
