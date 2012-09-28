#pragma once
#include "IComponent.h"
#include "core.h"

class CPosition2D : public IComponent
{
public:
	static const CID ID = CID::Position2D;
	Vector2F current;
	Vector2F previous;

	CPosition2D(float x, float y) : current(x, y), previous(x, y) {}
	CPosition2D(Vector2F pos) : current(pos), previous(pos) {}
};

