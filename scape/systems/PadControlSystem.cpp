#include <scape/stdafx.h>
#include <tile/components.h>
#include "PadControlSystem.h"
using namespace std;

vector<ISystem::ID> PadControlSystem::required_systems() const
{
	return ISystem::require();
}

std::vector<IComponent::ID> PadControlSystem::required_components() const
{
    return IComponent::require<CPadInput, CVelocity>();
}

PadControlSystem::PadControlSystem() {}

PadControlSystem::~PadControlSystem() {}

bool PadControlSystem::on_event(SDL_Event& event)
{
    return false;
}