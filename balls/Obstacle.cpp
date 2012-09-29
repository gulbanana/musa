#include <engine/misc.h>
#include <engine/components.h>
#include "Obstacle.h"

using namespace std;

Obstacle::Obstacle(Color4F color, Vector2F position)
{
	add_component(
		make_unique<CPosition2D>(position.x, position.y)
	);
	add_component(
		make_unique<CGeometry2D>(color, make_unique<Rectangle>(Rect4F(-40.f, -60.f, 40.f, 60.f)))
	);
	add_component(
		make_unique<CLabel>("wall")
	);
	add_component(
		make_unique<CCollision>(false, true)
	);
}
