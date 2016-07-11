#pragma once
#include <objidl.h>
#include <gdiplus.h>
#include "LineSegment2d.h"
#include "GameCamera.h"

class GraphicsManager {
	static GraphicsManager* instance;
	GraphicsManager();
	void drawBorder(Gdiplus::Graphics& g);
	void drawLine(Gdiplus::Graphics& g, Gdiplus::Color c, LineSegment2d ls);
public:

	GameCamera camera;

	static GraphicsManager* getInstance();
	void update(Gdiplus::Graphics& g);
};
