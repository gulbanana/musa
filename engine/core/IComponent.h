#pragma once
#include "Identified.h"

enum class CMP
{
	Acceleration,
	Label,
    Mesh,
	Player,
	Physics,
	Position,
	Scene,
	Transform,
	Velocity,
	Last = Velocity
};

class IComponent : public Identifiable<CMP>
{
public:
	~IComponent() {}
};