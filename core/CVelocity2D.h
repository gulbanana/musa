#pragma once
#include "IComponent.h"
#include "types.h"

class CVelocity2D : public IComponent
{
public:
	static const CID ID = CID::Velocity2D;
	Vector2F vector;

	CVelocity2D(float x, float y) : vector(x, y) {}
	CVelocity2D(Vector2F vel) : vector(vel) {}
};

