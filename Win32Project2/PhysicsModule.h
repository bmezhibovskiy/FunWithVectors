#pragma once
#include "GameModule.h"
#include "Vector3d.h"

class PhysicsModule : public GameModule {
public:

	static const double epsilon;

	//Input
	double frictionCoefficient;
	Vector3d acceleration;

	//Output
	Vector3d velocity;
	Vector3d position;

	
	PhysicsModule(GameObject* owner, Vector3d position);

	void update();

};
