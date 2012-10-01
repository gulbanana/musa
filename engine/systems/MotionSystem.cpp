#include <array>
#include <cmath>
#include <list>
#include <SDL_timer.h>
#include "../components.h"
#include "MotionSystem.h"
using namespace std;

vector<CMP> MotionSystem::required_components() const 
{
	array<CMP,2> cmpTypes = {CMP::Position, CMP::Velocity};
	return vector<CMP>(cmpTypes.begin(), cmpTypes.end());
}

vector<SYS> MotionSystem::required_systems() const 
{
	array<SYS,1> sysTypes = {SYS::Control};
	return vector<SYS>(sysTypes.begin(), sysTypes.end());
}

MotionSystem::MotionSystem(shared_ptr<GameState> s) : state(s) {}

void MotionSystem::on_frame()
{
	elapsedTime = state->last_frame_time / 1000.f;
}

void MotionSystem::on_entity(shared_ptr<IEntity> entity)
{
	auto position = entity->get_component<CPosition>();
	auto velocity = entity->get_component<CVelocity>();

	if (entity->has_component<CAcceleration>())
	{
		auto acceleration = entity->get_component<CAcceleration>();
		velocity->vector += acceleration->vector_change * elapsedTime;
		velocity->rotation += acceleration->rotation_change * elapsedTime;
	}

	position->previous_location = position->location;
	
	position->location += velocity->vector * elapsedTime;
	
	position->orientation += velocity->rotation * elapsedTime;
	position->orientation.mod(360.f);
}