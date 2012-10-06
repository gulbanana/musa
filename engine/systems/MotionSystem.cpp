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

void MotionSystem::pre_frame()
{
	elapsedTime = state->last_frame_time / (seconds)1000.0;
}

void MotionSystem::on_entity(shared_ptr<IEntity> entity)
{
	auto position = entity->get_component<CPosition>();
	auto velocity = entity->get_component<CVelocity>();

	if (entity->has_component<CAcceleration>())
	{
		auto acceleration = entity->get_component<CAcceleration>();
		velocity->vector += acceleration->vector_change * (coord)elapsedTime;
		velocity->rotation += acceleration->rotation_change * (degrees)elapsedTime;
	}

	position->previous_location = position->location;
	
	position->location += velocity->vector * (coord)elapsedTime;
	
	position->orientation += velocity->rotation * (degrees)elapsedTime;
	position->orientation.mod((degrees)360.0);
}