#pragma once
#include "IEntity.h"
#include <SFML/Graphics.hpp>

class Ball : public IEntity
{
public:
	Ball(sf::Color color, float x, float y);
};

