#pragma once
#include "IComponent.h"

class IArchetype
{
public:
	~IArchetype() {}
	virtual std::vector<IComponent*> components() = 0;
};