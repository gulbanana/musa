#pragma once
#include <engine/core.h>

class World
{
	std::vector<std::unique_ptr<IArchetype>> _archetypes;
public:
	std::vector<std::shared_ptr<IEntity>> entities;
	std::shared_ptr<IEntity> cameraEntity;
	World(bool is3d);
};

