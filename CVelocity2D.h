#pragma once
#include "IComponent.h"

class CVelocity2D : public IComponent
{
public:
	float x;
	float y;

	CVelocity2D(float posX, float posY) : x(posX), y(posY) {}
	std::string Name() { return "Velocity2D"; }
};

