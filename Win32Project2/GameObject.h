#pragma once
#include <vector>
#include "GameModule.h"
class GameModule;
enum GameModuleType;
class GameObject {
	std::vector<GameModule*> modules;
public:
	void addModule(GameModule* module);
	GameModule* moduleForType(GameModuleType type);
	void update();
};
