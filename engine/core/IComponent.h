#pragma once
#include "Identified.h"

enum class CMP
{
	Acceleration,
	Label,
	Input,
    Mesh,
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
	virtual ~IComponent() {}
	virtual std::unique_ptr<IComponent> clone() const = 0;
};