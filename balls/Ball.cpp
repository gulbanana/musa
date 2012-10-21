#include <engine/core.h>
#include <engine/components.h>
#include "Ball.h"
using namespace std;

Ball::Ball(IRenderable* mesh)
{
	_components.emplace_back(make_unique<CLabel>("ball"));
	_components.emplace_back(make_unique<CRenderable>(mesh));
	_components.emplace_back(make_unique<CPhysics>(true, true));
}
