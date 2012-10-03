#include <engine/misc.h>
#include <engine/components.h>
#include "Ball.h"
using namespace std;

Ball::Ball(coord radius, Colour4F colour, Vec2<coord> position, Vec2<coord> acceleration, bool solid)
{
	auto factory = PrimitiveFactory(make_shared<SolidColourBrush>(colour));

	add_component(make_unique<CLabel>("ball"));
	add_component(make_unique<CPosition>(position));
	add_component(make_unique<CVelocity>(acceleration));
	add_component(make_unique<CMesh>(factory.create_sphere(radius)));
	add_component(make_unique<CPhysics>(true, solid));
}
