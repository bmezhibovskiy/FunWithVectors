#include "ObjectManager.h"

ObjectManager* ObjectManager::instance = nullptr;

ObjectManager::ObjectManager() {}

void ObjectManager::update() {
	size_t numObjects = objects.size();
	for (size_t i = 0; i < numObjects; ++i) {
		objects[i]->update();
	}
}

ObjectManager* ObjectManager::getInstance() {
	if (instance == nullptr) {
		instance = new ObjectManager();
	}
	return instance;
}

void ObjectManager::addObject(GameObject* object) {
	if (object != 0) {
		objects.push_back(object);
	}
}