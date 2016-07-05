#include "InputManager.h"
#include "windows.h"

InputManager::InputManager() {

}

void InputManager::update() {
	for (int i = 0; i < 255; ++i) {
		previousKeys[i] = pressedKeys[i];
		pressedKeys[i] = GetAsyncKeyState(i) & 0x8000;
		triggeredKeys[i] = (previousKeys[i] == false && pressedKeys[i] == true);
	}
}


bool InputManager::keyPressed(int keyCode) {
	return pressedKeys[keyCode];
}

bool InputManager::keyTriggered(int keyCode) {
	return triggeredKeys[keyCode];
}
