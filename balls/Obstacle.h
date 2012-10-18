#pragma once
#include <engine/scene.h>

class Obstacle : public LeafNode
{
public:
	Obstacle(IModel* mesh, point position, angles rotation, bool solid = true);
};

