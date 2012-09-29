#pragma once
#include "Vector2F.h"

class Rect4F
{
public:

	Vector2F a;
	Vector2F b;

	Rect4F(float x1, float y1, float x2, float y2) : a(x1, y1), b(x2, y2) {}
	Rect4F(Vector2F vertexA, Vector2F vertexB) : a(vertexA), b(vertexB) {}
};
