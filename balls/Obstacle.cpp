#include <engine/components.h>
#include <engine/misc.h>
#include "Obstacle.h"

using namespace std;

Obstacle::Obstacle(Color4F color, Vector2F position)
{
	add_component(
		make_unique<CPosition2D>(position.x, position.y)
	);
	add_component(
		make_unique<CShapeGeometry>(Polygon::SQUARE, color, 50.f)
	);
	add_component(
		make_unique<CLabel>("wall")
	);
	add_component(
		make_unique<CCollision>(false, true)
	);
}
