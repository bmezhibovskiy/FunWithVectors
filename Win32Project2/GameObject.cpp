#include "GameObject.h"

void GameObject::addModule(GameModule& module) {
	modules.push_back(module);
}

GameModule* GameObject::moduleForType(GameModuleType type) {
	size_t numModules = modules.size();
	for (size_t i = 0; i < numModules; ++i) {
		if (modules[i].type == type) {
			return &(modules[i]);
		}
	}
	return NULL;
}

void GameObject::update() {
	size_t numModules = modules.size();
	for (size_t i = 0; i < numModules; ++i) {
		modules[i].update();
	}
}