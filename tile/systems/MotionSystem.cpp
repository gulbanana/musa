#include <tile/stdafx.h>
#include <tile/components.h>
#include <core/systems.h>
#include "MotionSystem.h"
using namespace std;

string MotionSystem::description() const
{
    return "2D physics engine";
}

vector<ISystem::ID> MotionSystem::required_systems() const
{
    return require<ControlSystem>();
}

vector<IComponent::ID> MotionSystem::required_components() const 
{
    return IComponent::require<CTransform, CVelocity>();
}

MotionSystem::MotionSystem(GameState* state) : _state(state) {}

void MotionSystem::on_frame_entity(std::shared_ptr<IEntity> e)
{
    auto transform = e->get_component<CTransform>();
    auto velocity = e->get_component<CVelocity>();

    transform->translate = transform->translate + (velocity->vector * (float)_state->last_frame_time / 1000.f);
}