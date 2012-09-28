#include <array>
#include "components.h"
#include "MotionSystem.h"
using namespace std;

vector<CID> MotionSystem::required_components()
{
	array<CID,2> compTypes = {CID::Position2D, CID::Velocity2D};
	return vector<CID>(compTypes.begin(), compTypes.end());
}

MotionSystem::MotionSystem(float boundsX, float boundsY) : levelWidth(boundsX), levelHeight(boundsY) {}

void MotionSystem::on_entity(shared_ptr<IEntity> entity)
{
	auto position = entity->get_component<CPosition2D>();
	auto velocity = entity->get_component<CVelocity2D>();
	auto geometry = entity->get_component<CShapeGeometry>();
		
	//Special temporary check: wall collisions
	bool outOfBoundsX = position->current.x - geometry->radius <= 0.f || (position->current.x + geometry->radius) >= levelWidth;
	bool outOfBoundsY = position->current.y - geometry->radius <= 0.f || (position->current.y + geometry->radius) >= levelHeight;

	if (outOfBoundsX) velocity->vector.x *= -1;
	if (outOfBoundsY) velocity->vector.y *= -1;

	position->previous = position->current;
	position->current += velocity->vector;
}