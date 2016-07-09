#include "Player.h"
#include "PlayerControlsModule.h"
#include "PhysicsModule.h"
#include "GraphicsModule.h"

Player::Player(Vector3d initialPosition) {
	addModule(new PlayerControlsModule(this));
	Vector3d pos = Vector3d(0.5, 0.5, 0.0);
	PhysicsModule* physics = new PhysicsModule(this, pos);
	physics->frictionCoefficient = -0.2;
	addModule(physics);
	GraphicsModule* graphics = new GraphicsModule(this);
	double size = 0.025;
	graphics->objectLines.push_back(LineSegment2d(size, 0, -size, size));
	graphics->objectLines.push_back(LineSegment2d(size, 0, -size, -size));
	graphics->objectLines.push_back(LineSegment2d(-size, size, -size, -size));
	addModule(graphics);
}