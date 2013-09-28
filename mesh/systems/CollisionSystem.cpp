#include <engine/mesh/core.h>
#include "../components.h"
#include <algorithm>
#include <iterator>
#include <typeinfo>
#include <tuple>
#include "CollisionSystem.h"
#include "collision/AABBDetector.h"
using namespace std;

vector<CMP> CollisionSystem::required_components() const 
{
	return IComponent::require(CMP::Transform, CMP::Renderable, CMP::Physics);
}

vector<SYS> CollisionSystem::required_systems() const 
{
	return ISystem::require(SYS::Motion);
}

CollisionSystem::CollisionSystem() : targets(), detectors()
{
	detectors.push_back(make_unique<AABBDetector>());
}

void CollisionSystem::on_add(shared_ptr<IEntity> new_entity)
{ 
	if (new_entity->get_component<CPhysics>()->solid)
		targets.push_back(new_entity);
}

void CollisionSystem::on_frame_start()
{
	remove_if(begin(targets), end(targets), [this](weak_ptr<IEntity> entity)
	{
		return entity.expired();
	});
}

//Operate on each subject-object pair. param entity is subject, objects are in vec targets
void CollisionSystem::on_frame_entity(shared_ptr<IEntity> sourceEntity)
{
	auto physics = sourceEntity->get_component<CPhysics>();
	if (!physics->can_collide) return;

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
		
		if (pairCollides) 
		{
			physics->collisions.push_back(targetEntity);
		}
	}
}

