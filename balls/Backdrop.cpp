#include <memory>
#include <random>
#include <engine/components.h>
#include <engine/misc.h>
#include "Backdrop.h"
using namespace std;

Backdrop::Backdrop(Color4F color, Vector2F position, float rotation)
{
	add_component(
		make_unique<CPosition2D>(position)
	);
	add_component(
		make_unique<CGeometry2D>(color, make_unique<Rectangle>(Rect4F(-40.f, -60.f, 40.f, 60.f)))
	);
	add_component(
		make_unique<CLabel>("mall")
	);
	add_component(
		make_unique<CVelocity2D>(0.f, 0.f, rotation)
	);
}
