#include <random>
#include <engine/components.h>
#include <engine/misc.h>
#include "LargeBall.h"
using namespace std;

LargeBall::LargeBall(Color4F color, Vector2F position, Vector2F acceleration)
{
	add_component(
		make_unique<CPosition2D>(position)
	);
	add_component(
		make_unique<CGeometry2D>(color, make_unique<Circle>(20.f))
	);
	add_component(
		make_unique<CVelocity2D>(acceleration, 0.f)
	);
	add_component(
		make_unique<CCollision>(true, true)
	);
	add_component(
		make_unique<CPhysics>()
	);
}
