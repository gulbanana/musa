#pragma once
#include "IComponent.h"

class Position2D : IComponent
{
public:
	double x;
	double y;

	Position2D(double posX, double posY) : x(posX), y(posY) {}
};

