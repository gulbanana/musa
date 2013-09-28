#include "stdafx.h"
#include <core/misc.h>
#include <mesh/components.h>
#include "Ball.h"
using namespace std;

Ball::Ball(IRenderable* mesh)
{
	_components.emplace_back(make_unique<CLabel>("ball"));
	_components.emplace_back(make_unique<CRenderable>(mesh));
	_components.emplace_back(make_unique<CPhysics>(true, true));
}
