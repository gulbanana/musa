#pragma once
#include <memory>
#include <vector>
#include <string>
#include "entities/IEntity.h"

class WorldImpl;

class World
{
	WorldImpl* _pimpl;
public:
	World(std::string title);
	void add_entity(std::shared_ptr<IEntity> entity);
	void play();
};

#define main SDL_main