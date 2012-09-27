#pragma once
#include <memory>
#include <vector>
#include "ISystem.h"

class WorldImpl;

class World
{
	WorldImpl* _pimpl;

public:
	World();

	void add_entity(std::shared_ptr<IEntity> entity);
	void add_system(std::unique_ptr<ISystem> system);
	void play();
};

