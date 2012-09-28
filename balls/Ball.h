#pragma once
#include <engine/IEntity.h>

class Ball : public IEntity
{
public:
	Ball(Color4F color, Vector2F position, Vector2F acceleration);
	Ball(Color4F color);
};

