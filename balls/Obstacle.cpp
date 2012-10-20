#include <engine/core.h>
#include <engine/components.h>
#include <random>
#include "Obstacle.h"
using namespace std;

Obstacle::Obstacle(IModel* mesh, bool solid)
{
	_components.emplace_back(make_unique<CMesh>(mesh));

	if (solid)
	{
		_components.emplace_back(make_unique<CLabel>("wall"));
		_components.emplace_back(make_unique<CPhysics>(false, true));
	}
	else
	{
		_components.emplace_back(make_unique<CLabel>("mall"));
	}
}