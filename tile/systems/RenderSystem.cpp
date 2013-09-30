#include <tile/stdafx.h>
#include <tile/components.h>
#include "RenderSystem.h"
#include "KBMControlSystem.h"
#include "PadControlSystem.h"
#include <algorithm>
using namespace std;

vector<ISystem::ID> RenderSystem::required_systems() const
{
	return ISystem::require<KBMControlSystem, PadControlSystem>();
}

std::vector<IComponent::ID> RenderSystem::required_components() const
{
    return IComponent::require<CDraw, CTransform>();
}

RenderSystem::RenderSystem(IBlitter* blitter, shared_ptr<GameState> state) : _blitter(blitter), _state(state) {}

RenderSystem::~RenderSystem() {}

void RenderSystem::on_frame_start()
{
	_tram = _blitter->get_tram();

	_tram->fill(tile('.'));
}

void RenderSystem::on_frame_entity(std::shared_ptr<IEntity> e)
{
    auto transform = e->get_component<CTransform>();
    auto drawable = e->get_component<CDraw>();

    _tram->draw(drawable->layout, transform->translate.x, transform->translate.y);
}