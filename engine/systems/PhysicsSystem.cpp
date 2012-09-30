#include <array>
#include "../components.h"
#include "PhysicsSystem.h"
using namespace std;

vector<IComponent::ID> PhysicsSystem::required_components()
{
	array<IComponent::ID,1> compTypes = {IComponent::ID::Physics};
	return vector<IComponent::ID>(compTypes.begin(), compTypes.end());
}

void PhysicsSystem::on_entity(shared_ptr<IEntity> entity)
{
	//auto physics = entity->get_component<CPhysics>();
	//auto velocity = entity->get_component<CVelocity2D>("Velocity2D");

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