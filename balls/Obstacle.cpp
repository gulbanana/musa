#include <engine/misc.h>
#include <engine/components.h>
#include "Obstacle.h"

using namespace std;

Obstacle::Obstacle(Color4F color, Vector2F position, float rotation) : Backdrop(color, position, rotation)
{
	add_component(
		make_unique<CExtents<Rect4F>>(
			static_pointer_cast<RectangleMesh>(
				get_component<CMesh>()->geometry
			)
		)
	);
	add_component(make_unique<CPhysics>(false, true));
}
