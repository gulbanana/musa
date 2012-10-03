#pragma once
#include <engine/core.h>

class Obstacle : public IEntity
{
public:
	Obstacle(Colour4F color, Vec2<coord> position, Vec3<degrees> rotation, bool solid = true);
	Obstacle(Colour4F color, Vec2<coord> position, degrees rotation, bool solid = true);
};

