#pragma once
#include "GameObject.h"
#include "Vector3d.h"
class Player : public GameObject {
public:
	Player(Vector3d initialPosition);
};