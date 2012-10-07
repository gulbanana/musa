#pragma once
#include <engine/scene.h>

class Ball : public LeafNode
{
public:
	Ball(IModel* mesh, Vec3<coord> position, Vec3<coord> acceleration, Vec3<degrees> rotation);
};

