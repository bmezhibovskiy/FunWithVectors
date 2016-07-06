#pragma once
#include "GameObject.h"
class GameObject;
enum GameModuleType {
	GameModuleType_Unspecified,
	GameModuleType_Physics,
	GameModuleType_Graphics
};

class GameModule {
public:

	GameModuleType type;

	GameModule(GameObject* owner, GameModuleType type);

	GameObject* owner;

	virtual void update() = 0;

};
