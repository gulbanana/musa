#pragma once
#include <memory>
#include <vector>
#include <string>
#include <engine/core.h>

class WorldImpl;

class World
{
	WorldImpl* _pimpl;
public:
	World(std::string title);
	void add_entity(std::unique_ptr<IEntity> entity);
	void add_system(std::unique_ptr<ISystem> system);
	void play();
};

#define main SDL_main