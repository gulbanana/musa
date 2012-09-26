#pragma once
#include "IEntity.h"
#include <SFML/Graphics.hpp>

class Obstacle : public IEntity
{
public:
	Obstacle(sf::Color color, float x, float y);
};

