#include <array>
#include "../components.h"
#include "MotionSystem.h"
using namespace std;

vector<IComponent::ID> MotionSystem::required_components()
{
	array<IComponent::ID,2> compTypes = {IComponent::ID::Position2D, IComponent::ID::Velocity2D};
	return vector<IComponent::ID>(compTypes.begin(), compTypes.end());
}

MotionSystem::MotionSystem(float boundsX, float boundsY) : levelWidth(boundsX), levelHeight(boundsY) {}

void MotionSystem::on_entity(shared_ptr<IEntity> entity)
{
	auto position = entity->get_component<CPosition2D>();
	auto velocity = entity->get_component<CVelocity2D>();
	auto geometry = entity->get_component<CGeometry2D>();
		
	//Special temporary check: wall collisions
	bool outOfBoundsX = geometry->bounds().left() + position->current.x <= 0.f ||
						geometry->bounds().right() + position->current.x >= levelWidth;
	bool outOfBoundsY = geometry->bounds().top() + position->current.x <= 0.f ||
						geometry->bounds().bottom() + position->current.x >= levelHeight;

	if (outOfBoundsX) velocity->vector.x *= -1;
	if (outOfBoundsY) velocity->vector.y *= -1;

	position->previous = position->current;
	position->current += velocity->vector;
}