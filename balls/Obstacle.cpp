#include "stdafx.h"
#include <core/misc.h>
#include <mesh/components.h>
#include <random>
#include "Obstacle.h"
using namespace std;

Obstacle::Obstacle(IRenderable* mesh, bool solid)
{
	_components.emplace_back(make_unique<CRenderable>(mesh));

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