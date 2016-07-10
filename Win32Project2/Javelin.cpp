#include "Javelin.h"
#include "Vector3d.h"
#include "GraphicsModule.h"
#include "PhysicsModule.h"

Javelin::Javelin(Vector3d initialPosition, Vector3d initialDirection, double power) {
	
	PhysicsModule* physics = new PhysicsModule(this, initialPosition);
	Vector3d velocity = initialDirection.normalized() * power;
	physics->velocity = velocity;
	addModule(physics);

	GraphicsModule* graphics = new GraphicsModule(this);
	double size = 0.02;
	graphics->objectLines.push_back(LineSegment2d(-size, 0, size, 0));
	addModule(graphics);
}