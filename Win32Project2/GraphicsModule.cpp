#include "GraphicsModule.h"
#include "PhysicsModule.h"

GraphicsModule::GraphicsModule(GameObject* owner) : GameModule(owner, GameModuleType_Unspecified) {}

void GraphicsModule::update() {

	PhysicsModule* physics = dynamic_cast<PhysicsModule*>(owner->moduleForType(GameModuleType_Physics));
	
	linesToDraw.clear();

	if (physics->velocity.lengthSquared() > 0.0) {
		Vector3d nextFramePosition = physics->position + (physics->velocity.normalized() * 0.025);
		LineSegment2d playerRepresentation = LineSegment2d(physics->position.x, physics->position.y, nextFramePosition.x, nextFramePosition.y);
		linesToDraw.push_back(playerRepresentation);
	}
	else {
		double size = 0.01;
		LineSegment2d playerRepresentationA = LineSegment2d(physics->position.x - size, physics->position.y, physics->position.x + size, physics->position.y);
		LineSegment2d playerRepresentationB = LineSegment2d(physics->position.x, physics->position.y - size, physics->position.x, physics->position.y + size);
		linesToDraw.push_back(playerRepresentationA);
		linesToDraw.push_back(playerRepresentationB);
	}
}