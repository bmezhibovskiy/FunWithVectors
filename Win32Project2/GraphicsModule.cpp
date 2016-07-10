#include "GraphicsModule.h"
#include "PhysicsModule.h"
#include "Matrix4x4.h"

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
		Matrix4x4 rotation = Matrix4x4::rotationZ(t);		
		//2) Translate
		Matrix4x4 translation = Matrix4x4::translate(physics->position);

		Matrix4x4 transformation = translation * rotation;

		Vector3d worldSpaceStart = transformation * c.start;
		Vector3d worldSpaceEnd = transformation * c.end;
		LineSegment2d worldSpaceLine = LineSegment2d(worldSpaceStart.x, worldSpaceStart.y, worldSpaceEnd.x, worldSpaceEnd.y);
		linesToDraw.push_back(worldSpaceLine);
	}
	
}