#pragma once
#include "IComponent.h"

class CVelocity2D : public Identified<IComponent, CID::Velocity2D>
{
public:
	Vector2F vector;
	float rotation;

	CVelocity2D(float x, float y, float r) : vector(x, y), rotation(r) {}
	CVelocity2D(Vector2F vel, float r) : vector(vel), rotation(r) {}
};

