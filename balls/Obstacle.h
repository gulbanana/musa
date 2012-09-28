#pragma once
#include <engine/IEntity.h>

class Obstacle : public IEntity
{
public:
	Obstacle(Color4F color, Vector2F position);
};

