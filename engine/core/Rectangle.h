#pragma once
#include "IDrawable.h"
#include "Rect4F.h"

class Rectangle : public IDrawable
{
	Rect4F bounds;
public:
	void draw() override;
	virtual Rect4F bounds2D();

	//general rect constructor
	Rectangle(Rect4F b) : bounds(b) {}
	Rectangle(float x1, float y1, float x2, float y2) : bounds(Rect4F(x1, y1, x2, y2)) {}
	//square constructor
	Rectangle(float radius) : bounds(-radius, -radius, radius, radius) {}	
};