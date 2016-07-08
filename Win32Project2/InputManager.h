#pragma once
#include "GameModule.h"

class InputManager {
	static InputManager* instance;
	InputManager();
	bool previousKeys[255] = { false };
	bool pressedKeys[255] = { false };
public:
	static InputManager* getInstance();
	void update();
	bool keyPressed(int keyCode);
	bool keyTriggered(int keyCode);

};
