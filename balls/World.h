#pragma once
#include <core/framework.h>
#include <mesh/ResourceManager.h>

class World
{
	std::vector<std::unique_ptr<IArchetype>> _archetypes;
	ResourceManager _loader;

public:
	std::vector<std::shared_ptr<IEntity>> entities;
	std::shared_ptr<IEntity> cameraEntity;
	World(bool is3d);
};

