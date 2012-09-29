#pragma once
#include "IComponent.h"

class CPosition2D : public IComponent
{
	IDENTIFIED(IComponent, Physics);
	Vector2F location;
	float orientation;
	CPosition2D(float x, float y) : location(x, y), orientation(0.f) {}
	CPosition2D(Vector2F pos) : location(pos), orientation(0.f) {}
};

