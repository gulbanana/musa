#pragma once
#include "IComponent.h"
#include "IArchetype.h"

class ArchetypeBase : public IArchetype
{
protected:
	std::vector<std::unique_ptr<IComponent>> _components;

public:
	virtual ~ArchetypeBase() = 0;
	std::vector<IComponent*> components() final;
};