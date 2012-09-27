#pragma once
#include "IComponent.h"

class CPosition2D : public IComponent
{
public:
	float x;
	float prevX;
	float y;
	float prevY;

	CPosition2D(float posX, float posY) : x(posX), prevX(posX), y(posY), prevY(posY) {}
	std::string Name() { return "Position2D"; }
};

