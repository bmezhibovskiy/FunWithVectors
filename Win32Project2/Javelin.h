#pragma once
#include "GameObject.h"
#include "Vector3d.h"

class Javelin : public GameObject {
public:
	Javelin::Javelin(Vector3d initialPosition, Vector3d initialDirection, double power);
};