#pragma once
#include "Vector2F.h"
#include "Box6F.h"

class Rect4F
{
	float x1, y1, x2, y2;

public:
	//accessors - interface with the rect any way you like
	float left() { return x1; }
	float bottom() { return y1; }
	float right() { return x2; }
	float top() { return y2; }
	Vector2F bottomLeft() { return Vector2F(x1,y1); }
	Vector2F topRight() { return Vector2F(x2,y2); }
	Vector2F origin() { return bottomLeft(); }
	float width() { return x2-x1; }
	float height() { return y2-y1; }

	///constructors
	Rect4F(float left, float bottom, float right, float top) : x1(left), y1(bottom), x2(right), y2(top) {}
	Rect4F(Vector2F bottomLeft, Vector2F topRight) : x1(bottomLeft.x), y1(bottomLeft.y), x2(topRight.x), y2(topRight.y) {}
	Rect4F(Vector2F origin, float width, float height) : x1(origin.x), y1(origin.y), x2(origin.x + width), y2(origin.y + height) {}

	//operators
	Rect4F operator+(Vector2F const&);

	//implicit conversion from 2d square to 3d cube
	operator Box6F();

	//utility methods
	static Rect4F unification(Rect4F const& a, Rect4F const& b);
	bool contains(float x, float y) const;
	bool contains(Vector2F const& point) const;
	bool intersects(Rect4F const& rectangle) const;
	bool intersects(Rect4F const& rectangle, Rect4F& intersection) const;
};
