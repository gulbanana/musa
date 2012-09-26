#pragma once
#include "IComponent.h"

class Position2D : public IComponent
{
public:
	float x;
	float y;

	Position2D(float posX, float posY) : x(posX), y(posY) {}
	std::string Name() { return "Position2D"; }
};

