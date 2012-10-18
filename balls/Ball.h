#pragma once
#include <engine/scene.h>

class Ball : public LeafNode
{
public:
	Ball(IModel* mesh, point position, point acceleration, angles rotation);
};

