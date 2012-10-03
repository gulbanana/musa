#pragma once
#include <engine/core.h>

class Obstacle : public IEntity
{
public:
	Obstacle(Color4F color, Vec2<coord> position, Vec3<degrees> rotation, bool solid = true);
	Obstacle(Color4F color, Vec2<coord> position, degrees rotation, bool solid = true);
};

