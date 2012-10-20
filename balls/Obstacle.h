#pragma once
#include <engine/archetypes.h>

class Obstacle : public PresetArchetype
{
public:
	Obstacle(IModel* mesh, bool solid = true);
};

