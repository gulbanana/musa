#pragma once
#include <string>

enum class CID
{
	Collision = 0,
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

