#include "Javelin.h"
#include "Vector3d.h"
#include "GraphicsModule.h"
#include "PhysicsModule.h"

Javelin::Javelin(Vector3d initialPosition, Vector3d initialDirection, double power) {
	addModule(new GraphicsModule(this));
	PhysicsModule* physics = new PhysicsModule(this, initialPosition);
	Vector3d velocity = initialDirection.normalized() * power;
	physics->velocity = velocity;
	addModule(physics);
}