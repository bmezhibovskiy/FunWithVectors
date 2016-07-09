#include "GraphicsModule.h"
#include "PhysicsModule.h"

GraphicsModule::GraphicsModule(GameObject* owner) : GameModule(owner, GameModuleType_Graphics) {}

void GraphicsModule::update() {

	PhysicsModule* physics = dynamic_cast<PhysicsModule*>(owner->moduleForType(GameModuleType_Physics));
	
	linesToDraw.clear();

	//Transform from object to world space	
	double t = atan2(physics->velocity.y, physics->velocity.x);
	if (physics->velocity.lengthSquared() < PhysicsModule::epsilon) {
		t = 0;
	}
	size_t numLines = objectLines.size();
	for (size_t i = 0; i < numLines; ++i) {
		LineSegment2d c = objectLines[i];
		//1) Rotate
		Vector3d worldSpaceStart = Vector3d(c.start.x*cos(t) - c.start.y*sin(t), c.start.x*sin(t) - c.start.y*cos(t), 0);
		Vector3d worldSpaceEnd = Vector3d(c.end.x*cos(t) - c.end.y*sin(t), c.end.x*sin(t) - c.end.y*cos(t), 0);
		//2) Translate
		worldSpaceStart = worldSpaceStart + physics->position;
		worldSpaceEnd = worldSpaceEnd + physics->position;
		LineSegment2d worldSpaceLine = LineSegment2d(worldSpaceStart.x, worldSpaceStart.y, worldSpaceEnd.x, worldSpaceEnd.y);
		linesToDraw.push_back(worldSpaceLine);
	}
	
}