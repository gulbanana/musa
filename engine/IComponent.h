#pragma once
#include "core.h"

enum class CID
{
	Collision,
	Label,
	Physics,
	Position2D,
	ShapeGeometry,
	Velocity2D
};

class IComponent
{
public:
	virtual ~IComponent() {}
};

