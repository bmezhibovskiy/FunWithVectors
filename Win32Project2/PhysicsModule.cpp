#include "PhysicsModule.h"

double epsilon = 1e-8;

void PhysicsModule::update() {
	if (velocity.lengthSquared() > epsilon) {
		double playerFriction = -0.2; //TODO: Pull friction out
		Vector3d friction = velocity * playerFriction;
		acceleration = acceleration + friction;
	}
	else {
		velocity = Vector3d(0, 0, 0);
	}

	velocity = velocity + acceleration;
	position = position + velocity;

	acceleration = Vector3d(0, 0, 0);
}
