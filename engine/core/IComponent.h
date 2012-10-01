#pragma once
#include "Identified.h"

enum class CMP
{
	Acceleration,
	Brush,
	Extents,
	Label,
    Mesh,
	Physics,
	Position,
	Velocity
};

class IComponent : public Identifiable<CMP>
{
public:
	~IComponent() {}
};