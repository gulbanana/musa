#include <memory>
#include <random>
#include <engine/components.h>
#include <engine/misc.h>
#include "Backdrop.h"
using namespace std;

Backdrop::Backdrop(Color4F color, Vector2F position)
{
	add_component(
		make_unique<CPosition2D>(position)
	);
	add_component(
		make_unique<CGeometry2D>(color, make_unique<Rectangle>(50.f))
	);
	add_component(
		make_unique<CLabel>("mall")
	);
}
