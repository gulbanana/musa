#pragma once
#include "IComponent.h"
#include <SFML/Graphics.hpp>

class CShapeGeometry : public IComponent
{
public:
	enum class Shape {SQUARE, CIRCLE};
	Shape shape;
	sf::Color color;
	float radius;

	CShapeGeometry(Shape s, sf::Color c, float r) : shape(s), color(c), radius(r) {}
	std::string Name() { return "ShapeGeometry"; }
};

