#include "Ball.h"
#include "CPosition2D.h"
#include "CShapeGeometry.h"
#include "CLabel.h"
#include "CVelocity2D.h"
#include "CCollision.h"
#include <memory>
#include <random>
using namespace std;

Ball::Ball(sf::Color color, float x, float y)
{
	add_component(
		new CPosition2D(x, y)
	);
	add_component(
		new CShapeGeometry(CShapeGeometry::Shape::CIRCLE, color, 45.f)
	);
	add_component(
		new CLabel("ball")
	);
	add_component(
		new CVelocity2D(
			(((float)rand() / (float)RAND_MAX) - 0.5f) * 10,
			(((float)rand() / (float)RAND_MAX) - 0.5f) * 10
		)
	);
	add_component(
		new CCollision()
	);
}
