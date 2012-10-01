#include <engine/misc.h>
#include <engine/components.h>
#include "Ball.h"
using namespace std;

Ball::Ball(float radius, Color4F color, Vector2F position, Vector2F acceleration, bool solid)
{
	add_component(make_unique<CLabel>("ball"));

	add_component(make_unique<CBrush>(color));

	add_component(make_unique<CPosition>(position));
	add_component(make_unique<CVelocity>(acceleration));

	auto geometry = make_shared<CircleMesh>(radius);
	add_component(make_unique<CMesh>(geometry));
	add_component(make_unique<CExtents<Rect4F>>(geometry));

	add_component(make_unique<CPhysics>(true, solid));
}
