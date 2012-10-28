#pragma once
#include "IEntity.h"
#include "IArchetype.h"

//produces some kind of entities, somehow
class IEntityFactory
{                                                                     
public:
	//interface
	virtual ~IEntityFactory() {}
	virtual std::unique_ptr<IEntity> create(IArchetype* archetype = nullptr) = 0;
};

