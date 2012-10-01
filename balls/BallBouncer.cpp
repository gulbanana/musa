#include <array>
#include <vector>
#include <engine/components.h>
#include "BallBouncer.h"
using namespace std;

vector<CID> BallBouncer::required_components()
{
	array<CID,3> compTypes = {CID::Physics, CID::Velocity, CID::Position};
	return vector<CID>(compTypes.begin(), compTypes.end());
}

void BallBouncer::on_entity(std::shared_ptr<IEntity> entity)
{
	auto physics = entity->get_component<CPhysics>();
	if (!physics->can_collide) return;

	auto sourcePosition = entity->get_component<CPosition>();
	auto sourceVelocity = entity->get_component<CVelocity>();

	for (auto other : physics->collisions)
	{
		auto targetPosition = other->get_component<CPosition>();

		//calculate angle of collision
		auto speed = sourceVelocity->vector.length();
		auto angleOfCollision = targetPosition->location - sourcePosition->location;
		angleOfCollision.normalize();
		
		
	}
			//Special temporary check: wall collisions
	//TODO move this to collision so that this system is not 2d-specific
	/*bool outOfBoundsX = geometry->bounds().left() + position->location.x <= 0.f ||
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
	}*/

	/*		if (entity->has_component("Collision"))
	{
		auto collision = entity->get_component<CCollision>("Collision");
		
		if (collision->collidedX)
		{
			velocity->vector.x *= -1.f;
			//position->current.x = position->previous.x;
		}
		if (collision->collidedY) 
		{
			velocity->vector.y *= -1.f;
			//position->current.y = position->previous.y;
		}
	}*/

}

