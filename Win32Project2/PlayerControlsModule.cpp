#include "PlayerControlsModule.h"
#include "InputManager.h"
#include "ObjectManager.h"
#include "PhysicsModule.h"
#include "Javelin.h"
#include "windows.h" //key codes

PlayerControlsModule::PlayerControlsModule(GameObject* owner) : GameModule(owner, GameModuleType_Unspecified) {}

void PlayerControlsModule::update() {
	
	PhysicsModule* physics = dynamic_cast<PhysicsModule*>(owner->moduleForType(GameModuleType_Physics));
	
	double speed = 0.0025;
	if (InputManager::getInstance()->keyPressed(VK_UP)) {
		physics->acceleration = physics->acceleration + Vector3d(0, -speed, 0);
	}
	if (InputManager::getInstance()->keyPressed(VK_DOWN)) {
		physics->acceleration = physics->acceleration + Vector3d(0, speed, 0);
	}
	if (InputManager::getInstance()->keyPressed(VK_LEFT)) {
		physics->acceleration = physics->acceleration + Vector3d(-speed, 0, 0);
	}
	if (InputManager::getInstance()->keyPressed(VK_RIGHT)) {
		physics->acceleration = physics->acceleration + Vector3d(speed, 0, 0);
	}

	if (InputManager::getInstance()->keyTriggered(VK_SPACE)) {
		Vector3d direction = Vector3d(0,1,0);
		if (physics->velocity.lengthSquared() > 0) {
			direction = physics->velocity;
		}
		Javelin* javelin = new Javelin(physics->position, direction, 0.1);
		ObjectManager::getInstance()->addObject(javelin);
	}
}
