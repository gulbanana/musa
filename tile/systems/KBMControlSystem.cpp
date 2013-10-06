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

    auto w_e = vec2(_keyboard.get_axis(SDLK_KP_4, SDLK_KP_6), 0) + vec2(_keyboard.get_axis(SDLK_a, SDLK_d), 0);
    auto s_n = vec2(0, _keyboard.get_axis(SDLK_KP_2, SDLK_KP_8)) + vec2(0, _keyboard.get_axis(SDLK_s, SDLK_w));
    auto sw_ne = vec2(_keyboard.get_axis(SDLK_KP_1, SDLK_KP_9), _keyboard.get_axis(SDLK_KP_1, SDLK_KP_9));
    auto nw_se = vec2(_keyboard.get_axis(SDLK_KP_7, SDLK_KP_3), _keyboard.get_axis(SDLK_KP_3, SDLK_KP_7));

    velocity->vector = (w_e + s_n + sw_ne + nw_se).normalise()*15;
}