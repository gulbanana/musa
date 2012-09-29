#pragma once
#include "Vector2F.h"

class Rect4F
{
	float x1, y1, x2, y2;

public:
	float left() { return x1; }
	float top() { return y1; }
	float right() { return x2; }
	float bottom() { return y2; }

	Vector2F topLeft() { return Vector2F(x1,y1); }
	Vector2F bottomRight() { return Vector2F(x2,y2); }
	Vector2F origin() { return topLeft(); }

	float width() { return x2-x1; }
	float height() { return y2-y1; }

	Rect4F(float left, float top, float right, float bottom) : x1(left), y1(top), x2(right), y2(bottom) {}
	Rect4F(Vector2F topLeft, Vector2F bottomRight) : x1(topLeft.x), y1(topLeft.y), x2(bottomRight.x), y2(bottomRight.y) {}
	Rect4F(Vector2F origin, float width, float height) : x1(origin.x), y1(origin.y), x2(origin.x + width), y2(origin.y + height) {}

	static Rect4F unify(Rect4F a, Rect4F b);
};
