#pragma once
#include "GameModule.h"

class PlayerControlsModule : public GameModule {
public:
	
	PlayerControlsModule(GameObject* owner);

	void update();

};
