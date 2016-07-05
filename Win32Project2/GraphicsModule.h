#pragma once
#include "GameModule.h"
#include "LineSegment2d.h"
#include <vector>

class GraphicsModule: public GameModule {
public:
	GraphicsModule(GameObject* owner);

	std::vector<LineSegment2d> linesToDraw;

	void update();

};
