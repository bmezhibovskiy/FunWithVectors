#include "InputManager.h"
#include "windows.h"

InputManager* InputManager::instance = nullptr;

InputManager::InputManager() {}

InputManager* InputManager::getInstance() {
	if (instance == nullptr) {
		instance = new InputManager();
	}
	return instance;
}

void InputManager::update() {
	for (int i = 0; i < 255; ++i) {
		previousKeys[i] = pressedKeys[i];
		pressedKeys[i] = static_cast<bool>(GetAsyncKeyState(i) & 0x8000);
	}
}

bool InputManager::keyPressed(int keyCode) {
	return pressedKeys[keyCode];
}

bool InputManager::keyTriggered(int keyCode) {
	return previousKeys[keyCode] == false && pressedKeys[keyCode] == true;
}
