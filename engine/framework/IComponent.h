#pragma once
#include "Identifiable.h"

enum class CMP
{
	Acceleration,
	Input,
	Label,
	Physics,
    Renderable,
	Transform,
	Velocity,
	COUNT
};

class IComponent : public Identifiable<CMP>
{
public:
	virtual ~IComponent() {}
	virtual std::unique_ptr<IComponent> clone() const = 0;
};