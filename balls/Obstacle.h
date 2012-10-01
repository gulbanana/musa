#pragma once
#include <engine/core.h>

class Obstacle : public IEntity
{
public:
	Obstacle(Color4F color, Vector2F position, Vector3F rotation, bool solid = true);
	Obstacle(Color4F color, Vector2F position, float rotation, bool solid = true);
};

