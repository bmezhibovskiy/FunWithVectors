#pragma once
#include "GameModule.h"

class InputManager {
	bool previousKeys[255] = { false };
	bool pressedKeys[255] = { false };
	bool triggeredKeys[255] = { false };
public:
	InputManager();
	void update();
	bool keyPressed(int keyCode);
	bool keyTriggered(int keyCode);

};
