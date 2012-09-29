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
	//square constructor
	Rectangle(float radius) : bounds(radius, radius, radius, radius) {}	
};