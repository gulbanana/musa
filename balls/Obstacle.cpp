#include <engine/core.h>
#include <engine/components.h>
#include <engine/misc.h>
#include <random>
#include "Obstacle.h"
using namespace std;

Obstacle::Obstacle(IModel* mesh, Vec3<coord> position, Vec3<degrees> rotation, bool solid)
{
	add_component(make_unique<CPosition>(position));
	add_component(make_unique<CMesh>(mesh));
	add_component(make_unique<CVelocity>(Vec3<coord>(0.0, 0.0, 0.0), rotation));

	if (solid)
	{
		add_component(make_unique<CLabel>("wall"));
		add_component(make_unique<CPhysics>(false, true));
	}
	else
	{
		add_component(make_unique<CLabel>("mall"));
	}
}