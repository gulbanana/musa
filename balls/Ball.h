#pragma once
#include <engine/scene.h>

class Ball : public LeafNode
{
public:
	Ball(coord radius, Colour4F color, Vec2<coord> position, Vec2<coord> acceleration, Vec3<degrees> rotation);
};

