#pragma once
#include "IComponent.h"
#include <SFML/Graphics.hpp>

class Drawable : IComponent
{
public:
	enum class Shape {SQUARE, CIRCLE};
	Shape shape;
	sf::Color color;

	Drawable(Shape s, sf::Color c) : shape(s), color(c) {}
};

