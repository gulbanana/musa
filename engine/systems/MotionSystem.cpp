#include <array>
#include <SDL_timer.h>
#include "../components.h"
#include "MotionSystem.h"
using namespace std;

vector<IComponent::ID> MotionSystem::required_components()
{
	array<IComponent::ID,2> compTypes = {IComponent::ID::Position2D, IComponent::ID::Velocity2D};
	return vector<IComponent::ID>(compTypes.begin(), compTypes.end());
}

MotionSystem::MotionSystem(shared_ptr<GameState> s, int x, int y) : state(s), levelWidth((float)x), levelHeight((float)y) {}

void MotionSystem::on_frame()
{
	elapsedTime = (SDL_GetTicks() - state->clock) / 1000.f;
}

void MotionSystem::on_entity(shared_ptr<IEntity> entity)
{
	auto position = entity->get_component<CPosition2D>();
	auto velocity = entity->get_component<CVelocity2D>();
	auto geometry = entity->get_component<CGeometry2D>();
		
	//Special temporary check: wall collisions
	bool outOfBoundsX = geometry->bounds().left() + position->location.x <= 0.f ||
						geometry->bounds().right() + position->location.x >= levelWidth;
	bool outOfBoundsY = geometry->bounds().top() + position->location.y <= 0.f ||
						geometry->bounds().bottom() + position->location.y >= levelHeight;

	if (outOfBoundsX) 
	{
		position->location.x = position->previous.x;
		velocity->vector.x *= -1;
	}
		
	if (outOfBoundsY) 
	{
		position->location.y = position->previous.y;
		velocity->vector.y *= -1;
	}

	position->previous = position->location;
	position->location += velocity->vector * elapsedTime;
	position->orientation = fmodf(position->orientation + velocity->rotation * elapsedTime, 360);
}