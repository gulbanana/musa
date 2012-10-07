#pragma once
#include <engine/scene.h>

class Obstacle : public LeafNode
{
public:
	Obstacle(IModel* mesh, Vec3<coord> position, Vec3<degrees> rotation, bool solid = true);
};

