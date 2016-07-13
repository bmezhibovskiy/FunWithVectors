#pragma once
#include "Vector3d.h"
#include "Matrix4x4.h"

class GameCamera {
	Vector3d position, direction;
public:
	GameCamera(Vector3d position, Vector3d direction);
	Matrix4x4 cameraTransformationMatrix();
	Matrix4x4 viewMatrix();
};