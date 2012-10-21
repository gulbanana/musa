#include <engine/core.h>
#include <engine/components.h>
#include <iostream>
#include "Bouncer.h"
using namespace std;
using namespace glm;

vector<IComponent::ID> Bouncer::required_components() const
{
	array<CMP,4> compTypes = {CMP::Physics, CMP::Velocity, CMP::Transform, CMP::Renderable};
	return vector<CMP>(compTypes.begin(), compTypes.end());
}

vector<ISystem::ID> Bouncer::required_systems() const
{
	array<SYS,3> compTypes = {SYS::Collision};
	return vector<SYS>(compTypes.begin(), compTypes.end());
}

Bouncer::Bouncer(int r) : _width((coord)r), _height((coord)r), _depth((coord)r)  {}

Bouncer::Bouncer(int x, int y, int z) : _width((coord)x), _height((coord)y), _depth((coord)z)  {}

void Bouncer::on_frame_entity(std::shared_ptr<IEntity> entity)
{
	auto physics = entity->get_component<CPhysics>();
	if (!physics->can_collide) return;

	auto position = entity->get_component<CTransform>();
	auto velocity = entity->get_component<CVelocity>();
	auto mesh = entity->get_component<CRenderable>();

	//Bounce type #1: walls, reflect by component inversion
	auto sourceBox = mesh->geometry->bounds();
	bool outOfBoundsX = sourceBox.left() + position->translate.x <= (coord)0.0 ||
						sourceBox.right() + position->translate.x >= _width;
	bool outOfBoundsY = sourceBox.bottom() + position->translate.y <= (coord)0.0 ||
						sourceBox.top() + position->translate.y >= _height;
	bool outOfBoundsZ = sourceBox.back() + position->translate.z <= (coord)0.0 ||
						sourceBox.front() + position->translate.z >= _depth;

	if (outOfBoundsX) 
	{
		velocity->vector.x *= -1;
        position->translate.x = glm::max(position->translate.x, sourceBox.right());
        position->translate.x = glm::min(position->translate.x, _width - sourceBox.right());
	}
		
	if (outOfBoundsY) 
	{
		velocity->vector.y *= -1;
        position->translate.y = glm::max(position->translate.y, sourceBox.top());
        position->translate.y = glm::min(position->translate.y, _height - sourceBox.top());
	}

	if (outOfBoundsZ) 
	{
		velocity->vector.z *= -1;
        position->translate.z = glm::max(position->translate.z, sourceBox.front());
        position->translate.z = glm::min(position->translate.z, _depth - sourceBox.front());
	}

	if (outOfBoundsX || outOfBoundsY || outOfBoundsZ)
	{
		return;
	}

	//Bounce type #2: objects, reflect by angle of target
	for (auto target : physics->collisions)
	{		
		auto targetPosition = target->get_component<CTransform>();

		//calculate angle of collision
		auto speed = length(velocity->vector);
		auto angleOfCollision = normalize(targetPosition->translate - position->translate);

		velocity->vector = angleOfCollision * (coord)-1 * (coord)speed;

		if (target->has_component<CVelocity>())
		{
			auto targetVelocity = target->get_component<CVelocity>();
			auto targetSpeed = length(targetVelocity->vector);

			//swap velocity
			if (targetSpeed > (coord)0 && speed > 0)
			{
				velocity->vector = normalize(velocity->vector);
				velocity->vector *= targetSpeed;

				targetVelocity->vector = normalize(targetVelocity->vector);
				targetVelocity->vector *= speed;
			}
			
			//equalise velocity
			/*if (targetSpeed > (coord)0)
			{
				auto speedDifference = (coord)(abs(speed - targetSpeed) / 2);

				if (speed > targetSpeed)
				{
					velocity->vector.normalize();
					targetVelocity->vector.normalize();
					velocity->vector *= speed - speedDifference;
					targetVelocity->vector *= targetSpeed + speedDifference;
				}

				if (targetSpeed > speed)
				{
					velocity->vector.normalize();
					targetVelocity->vector.normalize();
					velocity->vector *= speed + speedDifference;
					targetVelocity->vector *= targetSpeed - speedDifference;
				}
			}*/
			
		}
		
		return;
	}
}