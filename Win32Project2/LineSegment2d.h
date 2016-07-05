#pragma once
#include "Vector3d.h"

struct LineSegment2d {
	Vector3d start, end;
	LineSegment2d(double x1, double y1, double x2, double y2) : start(x1, y1, 0), end(x2, y2, 0) {}
};
