#pragma once
#include <engine/entities.h>

class Ball : public IEntity
{
public:
	Ball(coord radius, Colour4F color, Vec2<coord> position, Vec2<coord> acceleration, Vec3<degrees> rotation);
};

