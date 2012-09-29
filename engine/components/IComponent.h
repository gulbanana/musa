#pragma once
#include "../core.h"

class IComponent
{
	IDENTIFIABLE
	(
		Collision,
		Label,
		Physics,
		Position2D,
		Geometry2D,
		Velocity2D
	);

public:
	~IComponent() {}
};
