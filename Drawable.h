#pragma once
#include "IComponent.h"
#include <SFML/Graphics.hpp>

class Drawable : public IComponent
{
public:
	enum class Shape {SQUARE, CIRCLE};
	Shape shape;
	sf::Color color;
	std::string text;

	Drawable(Shape s, sf::Color c, std::string t) : shape(s), color(c), text(t) {}
	std::string Name() { return "Drawable"; }
};

