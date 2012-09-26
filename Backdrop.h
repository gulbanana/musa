#pragma once
#include "IEntity.h"
#include <SFML/Graphics.hpp>

class Backdrop : public IEntity
{
public:
	Backdrop(sf::Color color, float x, float y);
};

