#include <array>
#include <iterator>
#include <typeinfo>
#include <tuple>
#include "../../misc.h"
#include "../../components.h"
#include "CollisionSystem.h"
#include "RectIntersectionDetector.h"
using namespace std;

vector<IComponent::ID> CollisionSystem::required_components()
{
	array<IComponent::ID,3> compTypes = {IComponent::ID::Position, IComponent::ID::Extents, IComponent::ID::Physics};
	return vector<IComponent::ID>(compTypes.begin(), compTypes.end());
}

CollisionSystem::CollisionSystem()
{
	targets = vector<weak_ptr<IEntity>>();
	detectors = vector<unique_ptr<ICollisionDetector>>();
	detectors.push_back(make_unique<RectIntersectionDetector>());
}

void CollisionSystem::add_entity(weak_ptr<IEntity> new_entity)
{ 
	ISystem::add_entity(new_entity);
	if (new_entity.lock()->get_component<CPhysics>()->solid)
		targets.push_back(new_entity);
}

void CollisionSystem::on_frame()
{
	remove_if(begin(targets), end(targets), [](weak_ptr<IEntity> entity)
	{
		return entity.expired();
	});
}

//Operate on each subject-object pair. param entity is subject, objects are in vec targets
void CollisionSystem::on_entity(shared_ptr<IEntity> sourceEntity)
{
	auto physics = sourceEntity->get_component<CPhysics>();
	if (!physics->reactive) return;

	physics->collisions.clear();

	for (auto entity : targets)
	{
		auto targetEntity = entity.lock();
		if (sourceEntity.get() == targetEntity.get()) continue;

		auto pairCollides = true;

		for (auto& detector : detectors)
		{
			pairCollides = detector->collide(sourceEntity, targetEntity);
			if (!pairCollides) continue;
		}
		
		if (pairCollides) physics->collisions.push_back(targetEntity);
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
}

