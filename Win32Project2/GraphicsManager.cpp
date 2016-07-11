#include "GraphicsManager.h"
#include "ObjectManager.h"
#include "GraphicsModule.h"
#include "PhysicsModule.h"
#include "Matrix4x4.h"
#include <gdiplus.h>
using namespace Gdiplus;

GraphicsManager* GraphicsManager::instance = nullptr;

GraphicsManager::GraphicsManager() : camera(Vector3d(0.5,0.5,0.5), Vector3d(0,0,-1)) {}

GraphicsManager* GraphicsManager::getInstance() {
	if (instance == nullptr) {
		instance = new GraphicsManager();
	}
	return instance;
}

void GraphicsManager::drawBorder(Graphics& g) {
	Pen pen(Color(0, 0, 0), 2.0f);
	g.DrawLine(&pen, 100, 100, 600, 100);
	g.DrawLine(&pen, 100, 600, 600, 600);
	g.DrawLine(&pen, 100, 100, 100, 600);
	g.DrawLine(&pen, 600, 100, 600, 600);
}

void GraphicsManager::drawLine(Graphics& g, Color c, LineSegment2d ls) {
	Pen pen(c, 3.0f);
	g.DrawLine(&pen, (INT)(ls.start.x * 500 + 100), (INT)(ls.start.y * 500 + 100), (INT)(ls.end.x * 500 + 100), (INT)(ls.end.y * 500 + 100));
}

void GraphicsManager::update(Graphics& g) {

	g.Clear(Color(255, 255, 255));

	drawBorder(g); //TODO: Make the border walls objects?


	size_t numObjects = ObjectManager::getInstance()->objects.size();
	for (size_t i = 0; i < numObjects; ++i) {
		GameObject* object = ObjectManager::getInstance()->objects[i];
		if (object != NULL) {
			PhysicsModule* physics = dynamic_cast<PhysicsModule*>(object->moduleForType(GameModuleType_Physics));
			GraphicsModule* graphics = dynamic_cast<GraphicsModule*>(object->moduleForType(GameModuleType_Graphics));
			if (graphics != NULL && physics != NULL) {
				//Transform from object to world space	
				double t = atan2(physics->velocity.y, physics->velocity.x);
				if (physics->velocity.lengthSquared() < PhysicsModule::epsilon) {
					t = 0;
				}
				size_t numLines = graphics->objectLines.size();
				for (size_t i = 0; i < numLines; ++i) {
					LineSegment2d c = graphics->objectLines[i];
					//1) Rotate
					Matrix4x4 rotation = Matrix4x4::rotationZ(t);
					//2) Translate
					Matrix4x4 translation = Matrix4x4::translate(physics->position);

					Matrix4x4 transformation = translation * rotation;

					Vector3d worldSpaceStart = transformation * c.start;
					Vector3d worldSpaceEnd = transformation * c.end;
					LineSegment2d worldSpaceLine = LineSegment2d(worldSpaceStart.x, worldSpaceStart.y, worldSpaceEnd.x, worldSpaceEnd.y);

					LineSegment2d finalLine = worldSpaceLine;


					drawLine(g, graphics->color, finalLine);
				}
			}
		}
	}
}
