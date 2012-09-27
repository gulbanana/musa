#pragma once

#include "Point2F.h"

class Rect4F
{
public:

	Point2F a;
	Point2F b;

	Rect4F(float x1, float y1, float x2, float y2) : a(x1, y1), b(x2, y2) {}
	Rect4F(Point2F vertexA, Point2F vertexB) : a(vertexA), b(vertexB) {}
};
