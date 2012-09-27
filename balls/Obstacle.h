#pragma once
#include <core/IEntity.h>
#include <core/types.h>

class Obstacle : public IEntity
{
public:
	Obstacle(Color4F color, Vector2F position);
};

