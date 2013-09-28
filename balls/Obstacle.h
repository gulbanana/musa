#pragma once
#include <engine/mesh/archetypes.h>

class Obstacle : public PresetArchetype
{
public:
	Obstacle(IRenderable* mesh, bool solid = true);
};

