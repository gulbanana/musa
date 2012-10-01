#include <memory>
#include <random>
#include <engine/components.h>
#include <engine/misc.h>
#include "Backdrop.h"
using namespace std;

Backdrop::Backdrop(Color4F color, Vector2F position, float rotation)
{
	add_component(make_unique<CLabel>("wall"));
	add_component(make_unique<CPosition>(position));
	add_component(make_unique<CBrush>(color));
	add_component(make_unique<CMesh>(make_shared<RectangleMesh>(-40.f, -60.f, 40.f, 60.f)));
	add_component(make_unique<CVelocity>(Vector2F(), rotation));
}
