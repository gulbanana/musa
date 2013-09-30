#include <tile/stdafx.h>
#include "RenderSystem.h"
#include <algorithm>
using namespace std;

vector<ISystem::ID> RenderSystem::required_systems() const
{
	return require();
}

RenderSystem::RenderSystem(IBlitter* blitter, shared_ptr<GameState> state) : _blitter(blitter), _state(state) {}

RenderSystem::~RenderSystem() {}

void RenderSystem::on_wake()
{
	auto tram = _blitter->get_tram();

	tram->fill(tile('.'));
	tram->draw(tile('@', colour::GREEN), 35, 12);
}