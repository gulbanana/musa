#pragma once
#include <engine/entities.h>

class LargeBall : public IEntity
{
public:
	LargeBall(Color4F color, Vector2F position, Vector2F acceleration);
};

