#pragma once
#include "IComponent.h"

class CVelocity2D : public IComponent
{
	IDENTIFIED(IComponent, Physics);
	Vector2F vector;
	CVelocity2D(float x, float y) : vector(x, y) {}
	CVelocity2D(Vector2F vel) : vector(vel) {}
};

