#pragma once
#include "IComponent.h"

class CPosition2D : public IComponent
{
	IDENTIFIED(IComponent, Position2D);
	Vector2F previous;
	Vector2F location;
	float orientation;
	CPosition2D(float x, float y) : location(x,y), previous(x,y), orientation(0.f) {}
	CPosition2D(Vector2F pos) : location(pos), previous(pos), orientation(0.f) {}
};

