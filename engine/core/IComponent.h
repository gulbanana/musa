#pragma once
#include "Identified.h"

enum class CMP
{
	Acceleration,
	Label,
    Mesh,
	Physics,
	Position,
	Scene,
	Velocity,
	Last = Velocity
};

class IComponent : public Identifiable<CMP>
{
public:
	~IComponent() {}
};