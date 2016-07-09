#pragma once
#include "GameModule.h"
#include "LineSegment2d.h"
#include <vector>

class GraphicsModule: public GameModule {
public:
	GraphicsModule(GameObject* owner);
	
	//Input
	std::vector<LineSegment2d> objectLines; //In object space, anchor at 0,0

	//Output
	std::vector<LineSegment2d> linesToDraw;



	void update();

};
