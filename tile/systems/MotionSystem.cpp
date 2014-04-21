#include <tile/stdafx.h>
#include <tile/components.h>
#include "MotionSystem.h"
using namespace std;

vector<ISystem::ID> MotionSystem::required_systems() const
{
    return require();
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

    if (velocity->vector.x != 0) {
        printf("");
    }

    transform->translate = transform->translate + (velocity->vector * (float)_state->last_frame_time / 1000.f);
}