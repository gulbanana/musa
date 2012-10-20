#pragma once
#include "IEntityFactory.h"

//produces self-contained entities
class ManagedEntityFactory final : IEntityFactory
{
public:
	std::unique_ptr<IEntity> create(IArchetype* archetype = nullptr) final;
};

