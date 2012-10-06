#pragma once
#include <engine/scene.h>

class Obstacle : public LeafNode
{
public:
	Obstacle(IRenderable* mesh, Vec2<coord> position, Vec3<degrees> rotation, bool solid = true);
};

