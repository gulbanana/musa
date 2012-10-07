#include <engine/misc.h>
#include <engine/components.h>
#include "Ball.h"
using namespace std;

Ball::Ball(IModel* mesh, Vec2<coord> position, Vec2<coord> acceleration, Vec3<degrees> rotation)
{
	add_component(make_unique<CLabel>("ball"));
	add_component(make_unique<CPosition>(position));
	add_component(make_unique<CVelocity>(acceleration, rotation));
	add_component(make_unique<CMesh>(mesh));
	add_component(make_unique<CPhysics>(true, true));
}
