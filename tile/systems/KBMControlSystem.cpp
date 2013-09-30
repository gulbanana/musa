#include <tile/stdafx.h>
#include <tile/components.h>
#include "KBMControlSystem.h"
#include <iostream>
using namespace std;

vector<ISystem::ID> KBMControlSystem::required_systems() const
{
	return ISystem::require();
}

std::vector<IComponent::ID> KBMControlSystem::required_components() const
{
    return IComponent::require<CKBMInput, CVelocity>();
}

KBMControlSystem::KBMControlSystem() {}

KBMControlSystem::~KBMControlSystem() {}

bool KBMControlSystem::on_event(SDL_Event& event)
{
    _keyboard.handle(event);
    _mouse.handle(event);

    return false;
}

void KBMControlSystem::on_frame_entity(shared_ptr<IEntity> e)
{
    auto velocity = e->get_component<CVelocity>();

    auto w_e = vec2(_keyboard.get_axis(SDLK_KP4, SDLK_KP6), 0);
    auto s_n = vec2(0, _keyboard.get_axis(SDLK_KP2, SDLK_KP8));
    auto sw_ne = vec2(_keyboard.get_axis(SDLK_KP1, SDLK_KP9), _keyboard.get_axis(SDLK_KP1, SDLK_KP9));
    auto nw_se = vec2(_keyboard.get_axis(SDLK_KP7, SDLK_KP3), _keyboard.get_axis(SDLK_KP3, SDLK_KP7));

    velocity->vector = (w_e + s_n + sw_ne + nw_se).normalise()*0.15;
}