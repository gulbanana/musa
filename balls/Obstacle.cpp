#include <memory>
#include <random>
#include <engine/components.h>
#include <engine/misc.h>
#include "Obstacle.h"
using namespace std;

Obstacle::Obstacle(Color4F color, Vector2F position, Vector3F rotation, bool solid)
{
	add_component(make_unique<CPosition>(position));
	add_component(make_unique<CBrush>(color));
	add_component(make_unique<CMesh>(make_shared<RectangularPrismMesh>(Box6F(-40.f, -60.f, -40.f, 40.f, 60.f, 40.f))));
	add_component(make_unique<CVelocity>(Vector2F(), rotation));

	if (solid)
	{
		add_component(make_unique<CLabel>("wall"));
		add_component(make_unique<CExtents<Rect4F>>(static_pointer_cast<RectangleMesh>(get_component<CMesh>()->geometry)));
		add_component(make_unique<CPhysics>(false, true));
	}
	else
	{
		add_component(make_unique<CLabel>("mall"));
	}
}