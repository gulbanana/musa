#include <array>
#include <cmath>
#include <SDL_timer.h>
#include "../components.h"
#include "MotionSystem.h"
using namespace std;

vector<CID> MotionSystem::required_components()
{
	array<CID,2> compTypes = {CID::Position, CID::Velocity};
	return vector<CID>(compTypes.begin(), compTypes.end());
}

MotionSystem::MotionSystem(shared_ptr<GameState> s, int x, int y) : state(s), levelWidth((float)x), levelHeight((float)y) {}

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