#pragma once
#include <engine/entities.h>

class Ball : public IEntity
{
public:
	Ball(float radius, Color4F color, Vector2F position, Vector2F acceleration, bool solid = false);
};

