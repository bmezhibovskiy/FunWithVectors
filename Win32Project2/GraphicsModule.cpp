#include "GraphicsModule.h"
#include "PhysicsModule.h"
#include "Matrix4x4.h"

GraphicsModule::GraphicsModule(GameObject* owner) : GameModule(owner, GameModuleType_Graphics), color(0, 0, 0) {}

void GraphicsModule::update() {	
	
}