#pragma once
#include <engine/archetypes.h>

class Obstacle : public PresetArchetype
{
public:
	Obstacle(IRenderable* mesh, bool solid = true);
};

