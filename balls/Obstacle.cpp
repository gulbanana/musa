#include <memory>
#include <random>
#include <core/CCollision.h>
#include <core/CPosition2D.h>
#include <core/CShapeGeometry.h>
#include <core/CLabel.h>
#include "Obstacle.h"

using namespace std;

Obstacle::Obstacle(sf::Color color, float x, float y)
{
	add_component(
		new CPosition2D(x, y)
	);
	add_component(
		new CShapeGeometry(CShapeGeometry::Shape::SQUARE, color, 50.f)
	);
	add_component(
		new CLabel("wall")
	);
	add_component(
		new CCollision()
	);
}
