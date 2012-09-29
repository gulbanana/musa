#pragma once
#include "IDrawable.h"

class Circle : public IDrawable
{
	float radius;
public:
	void draw() override;
	virtual Rect4F bounds2D();

	Circle(float);
};

