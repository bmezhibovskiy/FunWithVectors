#include "GameCamera.h"
#include "Vector3d.h"
#include "Matrix4x4.h"

GameCamera::GameCamera(Vector3d position, Vector3d direction) : position(position), direction(direction) {}

Matrix4x4 GameCamera::cameraTransformationMatrix() {
	return Matrix4x4::translate(position);
}

Matrix4x4 GameCamera::viewMatrix() {
	return cameraTransformationMatrix();
}