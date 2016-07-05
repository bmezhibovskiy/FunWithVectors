#include "GameModule.h"
#include "GameObject.h"

GameModule::GameModule(GameObject* owner, GameModuleType type) : owner(owner), type(type) {}