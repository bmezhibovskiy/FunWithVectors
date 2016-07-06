#pragma once
#include "GameModule.h"
#include "Vector3d.h"

class PhysicsModule : public GameModule {
public:
	Vector3d position;
	Vector3d velocity;
	Vector3d acceleration;
	PhysicsModule(GameObject* owner, Vector3d position);

	void update();

};
