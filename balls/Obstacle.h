#pragma once
#include <core/framework.h>
#include <mesh/geometry.h>

class Obstacle : public ArchetypeBase
{
public:
	Obstacle(IRenderable* mesh, bool solid = true);
};

