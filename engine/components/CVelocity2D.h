#pragma once
#include "IComponent.h"

class CVelocity2D : public IComponent
{
	IDENTIFIED(IComponent, Velocity2D);

	Vector2F vector;
	float rotation;

	CVelocity2D(float x, float y, float r) : vector(x, y), rotation(r) {}
	CVelocity2D(Vector2F vel, float r) : vector(vel), rotation(r) {}
};

