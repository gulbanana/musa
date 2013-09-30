#pragma once
#include "Identifiable.h"

class IComponent : public Identifiable<IComponent>
{
public:
	virtual ~IComponent() {}
	virtual std::unique_ptr<IComponent> clone() const = 0;
};