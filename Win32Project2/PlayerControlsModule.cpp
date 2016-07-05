#include "PlayerControlsModule.h"
#include "InputManager.h"
#include "PhysicsModule.h"
#include "windows.h" //key codes

PlayerControlsModule::PlayerControlsModule(GameObject* owner) : GameModule(owner, GameModuleType_Unspecified) {}

void PlayerControlsModule::update() {

	//TODO: Remove hack and make input manager a singleton
	InputManager* inputManager = new InputManager();
	inputManager->update();

	PhysicsModule* physics = dynamic_cast<PhysicsModule*>(owner->moduleForType(GameModuleType_Physics));
	
	double speed = 0.0025;
	if (inputManager->keyPressed(VK_UP)) {
		physics->acceleration = physics->acceleration + Vector3d(0, -speed, 0);
	}
	if (inputManager->keyPressed(VK_DOWN)) {
		physics->acceleration = physics->acceleration + Vector3d(0, speed, 0);
	}
	if (inputManager->keyPressed(VK_LEFT)) {
		physics->acceleration = physics->acceleration + Vector3d(-speed, 0, 0);
	}
	if (inputManager->keyPressed(VK_RIGHT)) {
		physics->acceleration = physics->acceleration + Vector3d(speed, 0, 0);
	}
}
