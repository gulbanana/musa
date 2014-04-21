#include <mesh/stdafx.h>
#include <mesh/components.h>
#include <core/systems.h>
#include <cmath>
#include <list>
#include "MotionSystem.h"
using namespace std;

string MotionSystem::description() const
{
    return "Physics";
}

vector<IComponent::ID> MotionSystem::required_components() const 
{
	return IComponent::require<CTransform, CVelocity>();
}

vector<ISystem::ID> MotionSystem::required_systems() const 
{
	return ISystem::require<ControlSystem>();
}

MotionSystem::MotionSystem(GameState* s) : _state(s) {}

void MotionSystem::on_frame_start()
{
	elapsedTime = _state->last_frame_time * (seconds)0.001;
}

void MotionSystem::on_frame_entity(shared_ptr<IEntity> entity)
{
	auto position = entity->get_component<CTransform>();
	auto velocity = entity->get_component<CVelocity>();

	if (entity->has_component<CAcceleration>())
	{
		auto acceleration = entity->get_component<CAcceleration>();
		
		velocity->vector += acceleration->vector_change * (coord)elapsedTime;

		auto rotated = acceleration->versor_change * velocity->versor;
		velocity->versor = glm::mix(velocity->versor, rotated, (coord)elapsedTime);
		velocity->versor = glm::normalize(velocity->versor);
	}
	
	position->translate += velocity->vector * (coord)elapsedTime;

	auto rotated = velocity->versor * position->rotate;
	position->rotate = glm::mix(position->rotate, rotated, (coord)elapsedTime);
	position->rotate = glm::normalize(position->rotate);
}