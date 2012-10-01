#pragma once
#include <engine/entities.h>
#include "Backdrop.h"

class Obstacle : public Backdrop
{
public:
	Obstacle(Color4F color, Vector2F position, float rotation);
};

