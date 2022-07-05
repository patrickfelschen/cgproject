#include "Maths.hpp"

Maths::Maths()
{
}

Maths::~Maths()
{
}

Matrix Maths::createTransformationMatrix(const Vector& translation, const float& rx, const float& ry, const float& rz, const float& scale)
{
	Matrix transMat, rotXMat, rotYMat, rotZMat, scaleMat;

	transMat.translation(translation);

	rotXMat.rotationX(toRadians(rx));
	rotYMat.rotationY(toRadians(ry));
	rotZMat.rotationZ(toRadians(rz));

	scaleMat.scale(scale);
	
	return transMat * rotZMat * rotYMat * rotXMat * scaleMat;
}

Matrix Maths::createViewMatrix(Camera camera)
{
	Matrix transMat, rotMat;

	Vector cameraPos = camera.getPosition();
	Vector negativeCameraPos = Vector(-cameraPos.X, -cameraPos.Y, -cameraPos.Z);
	transMat.translation(negativeCameraPos);

	rotMat.rotationYawPitchRoll(Vector(toRadians(camera.getYaw()), toRadians(camera.getPitch()), toRadians(camera.getRoll())));

	return transMat * rotMat;
	
}

float Maths::toRadians(const float& value)
{
	return value * (M_PI / 180);
}
