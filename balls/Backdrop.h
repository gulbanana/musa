#pragma once
#include <core/IEntity.h>
#include <core/types.h>

class Backdrop : public IEntity
{
public:
	Backdrop(Color4F color, Vector2F position);
};

