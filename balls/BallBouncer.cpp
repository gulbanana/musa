#include <array>
#include <vector>
#include <engine/misc.h>
#include <engine/components.h>
#include <engine/systems/collision/Bounder2D.h>
#include "BallBouncer.h"
using namespace std;

vector<IComponent::ID> BallBouncer::required_components() const
{
	array<CMP,4> compTypes = {CMP::Physics, CMP::Velocity, CMP::Position, CMP::Extents};
	return vector<CMP>(compTypes.begin(), compTypes.end());
}

vector<ISystem::ID> BallBouncer::required_systems() const
{
	array<SYS,3> compTypes = {SYS::Collision};
	return vector<SYS>(compTypes.begin(), compTypes.end());
}

BallBouncer::BallBouncer(int x, int y) : 
	_width((float)x), 
	_height((float)y),
	_bounder(make_unique<Bounder2D>())
{}

void BallBouncer::on_entity(std::shared_ptr<IEntity> entity)
{
	auto physics = entity->get_component<CPhysics>();
	if (!physics->can_collide) return;

	auto position = entity->get_component<CPosition>();
	auto velocity = entity->get_component<CVelocity>();
	auto extents = entity->get_component<CExtents<Rect4F>>();

	//Bounce type #1: walls, reflect by component inversion
	auto sourceBox = extents->bounds->accept(_bounder.get());
	bool outOfBoundsX = sourceBox.left() + position->location.x <= 0.f ||
						sourceBox.right() + position->location.x >= _width;
	bool outOfBoundsY = sourceBox.bottom() + position->location.y <= 0.f ||
						sourceBox.top() + position->location.y >= _height;

	if (outOfBoundsX) 
	{
		velocity->vector.x *= -1;
	}
		
	if (outOfBoundsY) 
	{
		velocity->vector.y *= -1;
	}

	if (outOfBoundsX || outOfBoundsY)
	{
		//maybe? this would create a "forcefield" but prevent double-collisions
		position->location = position->previous_location;	
		return;
	}

	//Bounce type #2: objects, reflect by angle of target
	for (auto other : physics->collisions)
	{
		position->location = position->previous_location;	
		auto targetPosition = other->get_component<CPosition>();

		//calculate angle of collision
		auto speed = velocity->vector.length();
		auto angleOfCollision = targetPosition->location - position->location;
		angleOfCollision.normalize();

		velocity->vector = angleOfCollision * -1 * speed;

		//velocity->vector  = velocity->vector * -1;
	}
			//Special temporary check: wall collisions
	//TODO move this to collision so that this system is not 2d-specific
	/**/

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

