#pragma once
#include "IComponent.h"
#include <SFML/Graphics.hpp>

class CCollision : public IComponent
{
public:
	bool collidedX;
	bool collidedY;

	CCollision() : collidedX(false), collidedY(false) {}
	std::string Name() { return "Collision"; }
};

