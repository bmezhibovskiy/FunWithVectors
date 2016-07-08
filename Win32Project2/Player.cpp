#include "Player.h"
#include "PlayerControlsModule.h"
#include "PhysicsModule.h"
#include "GraphicsModule.h"

Player::Player(Vector3d initialPosition) {
	addModule(new PlayerControlsModule(this));
	PhysicsModule* physics = new PhysicsModule(this, Vector3d(0.5, 0.5, 0.0));
	physics->frictionCoefficient = -0.2;
	addModule(physics);
	addModule(new GraphicsModule(this));
}