#pragma once
#include "GameModule.h"
#include "LineSegment2d.h"
#include <vector>
#include <objidl.h>
#include <gdiplus.h>

class GraphicsModule: public GameModule {
public:
	GraphicsModule(GameObject* owner);
	
	std::vector<LineSegment2d> objectLines; //In object space, anchor at 0,0
	Gdiplus::Color color;
	
	void update();

};
