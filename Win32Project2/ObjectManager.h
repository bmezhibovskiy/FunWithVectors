#pragma once
#include <vector>
#include "GameObject.h"

class ObjectManager {
	static ObjectManager* instance;
	ObjectManager();	
public:
	std::vector<GameObject*> objects; //TODO: Make private?
	static ObjectManager* getInstance();
	void addObject(GameObject* object);
	void update();

};