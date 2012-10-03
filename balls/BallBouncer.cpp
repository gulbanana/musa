#include <array>
#include <algorithm>
#include <vector>
#include <engine/misc.h>
#include <engine/components.h>
#include "BallBouncer.h"
using namespace std;

vector<IComponent::ID> BallBouncer::required_components() const
{
	array<CMP,4> compTypes = {CMP::Physics, CMP::Velocity, CMP::Position, CMP::Mesh};
	return vector<CMP>(compTypes.begin(), compTypes.end());
}

vector<ISystem::ID> BallBouncer::required_systems() const
{
	array<SYS,3> compTypes = {SYS::Collision};
	return vector<SYS>(compTypes.begin(), compTypes.end());
}

BallBouncer::BallBouncer(int x, int y) : _width((float)x), _height((float)y) {}

void BallBouncer::on_entity(std::shared_ptr<IEntity> entity)
{
	auto physics = entity->get_component<CPhysics>();
	if (!physics->can_collide) return;

	auto position = entity->get_component<CPosition>();
	auto velocity = entity->get_component<CVelocity>();
	auto mesh = entity->get_component<CMesh>();

	//Bounce type #1: walls, reflect by component inversion
	auto sourceBox = mesh->geometry->bounds();
	bool outOfBoundsX = sourceBox.left() + position->location.x <= 0.f ||
						sourceBox.right() + position->location.x >= _width;
	bool outOfBoundsY = sourceBox.bottom() + position->location.y <= 0.f ||
						sourceBox.top() + position->location.y >= _height;

	if (outOfBoundsX) 
	{
		velocity->vector.x *= -1;
        position->location.x = max(position->location.x, sourceBox.right());
        position->location.x = min(position->location.x, _width - sourceBox.right());
	}
		
	if (outOfBoundsY) 
	{
		velocity->vector.y *= -1;
        position->location.y = max(position->location.y, sourceBox.top());
        position->location.y = min(position->location.y, _height - sourceBox.top());
	}

	if (outOfBoundsX || outOfBoundsY)
	{
		return;
	}

	//Bounce type #2: objects, reflect by angle of target
	for (auto other : physics->collisions)
	{		
		auto targetPosition = other->get_component<CPosition>();

		//calculate angle of collision
		auto speed = velocity->vector.length();
		auto angleOfCollision = targetPosition->location - position->location;
		angleOfCollision.normalize();

		velocity->vector = angleOfCollision * -1 * speed;
		//position->location = position->previous_location;
		//targetPosition->location = targetPosition->previous_location;
		return;
	}
}

bool BallBouncer::on_event(SDL_Event& event)
{
	if (event.type == SDL_VIDEORESIZE)
	{
		_width = (float)event.resize.w;
		_height = (float)event.resize.h;

		for (auto weakentity : entities)
		{
			auto entity = weakentity.lock();
			auto position = entity->get_component<CPosition>();
			auto mesh = entity->get_component<CMesh>();
			auto box = mesh->geometry->bounds();

			position->location.x = min(position->location.x, _width - box.right());
			position->location.y = min(position->location.y, _width - box.top());
		}
	}
	
	return false;
}