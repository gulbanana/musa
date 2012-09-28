#pragma once
#include "core.h"

class IComponent
{
	IDENTIFIABLE
	(
		Collision,
		Label,
		Physics,
		Position2D,
		ShapeGeometry,
		Velocity2D
	);

public:
	~IComponent() {}
};
