#include "Obstacle.h"
#include "CPosition2D.h"
#include "CShapeGeometry.h"
#include "CLabel.h"
#include "CCollision.h"
#include <memory>
#include <random>
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
