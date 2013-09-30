#include <tile/stdafx.h>
#include "RenderSystem.h"
using namespace std;

vector<ISystem::ID> RenderSystem::required_systems() const
{
	return require();
}

RenderSystem::RenderSystem(IBlitter* blitter) : _blitter(blitter)
{
}

RenderSystem::~RenderSystem(void)
{
}

void RenderSystem::on_wake()
{
	auto tram = _blitter->get_tram();

	tram->fill('.');
	tram->draw(tile('@'), 35, 12);
}