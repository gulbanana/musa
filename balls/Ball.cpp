#include <random>
#include <engine/components.h>
#include <engine/misc.h>
#include "Ball.h"
using namespace std;

Ball::Ball(Color4F color)
{
	add_component(
		make_unique<CPosition2D>(
			((float)rand() / (float)RAND_MAX) * 800,
			((float)rand() / (float)RAND_MAX) * 800
		)
	);
	add_component(
		make_unique<CShapeGeometry>(Polygon::CIRCLE, color, 10.f)
	);
	add_component(
		make_unique<CVelocity2D>(
			(((float)rand() / (float)RAND_MAX) - 0.5f) * 10,
			(((float)rand() / (float)RAND_MAX) - 0.5f) * 10
		)
	);
	add_component(
		make_unique<CCollision>(true, false)
	);
	add_component(
		make_unique<CPhysics>()
	);
}

Ball::Ball(Color4F color, Vector2F position, Vector2F acceleration)
{
	add_component(
		make_unique<CPosition2D>(position)
	);
	add_component(
		make_unique<CShapeGeometry>(Polygon::CIRCLE, color, 20.f)
	);
	add_component(
		make_unique<CVelocity2D>(acceleration)
	);
	add_component(
		make_unique<CCollision>(true, true)
	);
	add_component(
		make_unique<CPhysics>()
	);
}
