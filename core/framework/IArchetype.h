#pragma once
#include "IComponent.h"

class IArchetype
{
public:
	virtual ~IArchetype() {}
	virtual std::vector<IComponent*> components() = 0;
};