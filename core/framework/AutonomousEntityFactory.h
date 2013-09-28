#pragma once
#include "IEntityFactory.h"

//produces self-contained entities
class AutonomousEntityFactory final : IEntityFactory
{
public:
	std::unique_ptr<IEntity> create(IArchetype* archetype = nullptr) final;
};

