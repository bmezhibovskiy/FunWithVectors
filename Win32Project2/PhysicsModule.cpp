#include "PhysicsModule.h"
#include "GameObject.h"
#include "Vector3d.h"

double epsilon = 1e-8;

PhysicsModule::PhysicsModule(GameObject* owner, Vector3d position) : 
	GameModule(owner, GameModuleType_Physics), position(position), velocity(0, 0, 0), acceleration(0, 0, 0), frictionCoefficient(0) {}

void PhysicsModule::update() {
	if (velocity.lengthSquared() > epsilon) {
		Vector3d friction = velocity * frictionCoefficient;
		acceleration = acceleration + friction;
	}
	else {
		velocity = Vector3d(0, 0, 0);
	}

	velocity = velocity + acceleration;
	position = position + velocity;

	acceleration = Vector3d(0, 0, 0);
}
