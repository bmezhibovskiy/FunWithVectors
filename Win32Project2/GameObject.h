#pragma once
#include <vector>
#include "GameModule.h"

class GameObject {
	std::vector<GameModule> modules;
public:
	void addModule(GameModule& module);
	GameModule* moduleForType(GameModuleType type);
	void update();
};
