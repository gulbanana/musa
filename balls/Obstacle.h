#pragma once
#include <engine/scene.h>

class Obstacle : public LeafNode
{
public:
	Obstacle(Colour4F color, Vec2<coord> position, Vec3<degrees> rotation, bool solid = true);
	Obstacle(Colour4F color, Vec2<coord> position, degrees rotation, bool solid = true);
};

