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
	array<IComponent::ID,3> compTypes = {IComponent::ID::Position2D, IComponent::ID::Geometry2D, IComponent::ID::Collision};
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
	if (new_entity.lock()->get_component<CCollision>()->object)
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
	auto collision = sourceEntity->get_component<CCollision>();
	if (!collision->subject) return;
	auto position = sourceEntity->get_component<CPosition2D>();
	auto geometry = sourceEntity->get_component<CGeometry2D>();

	collision->collisions.clear();

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
		
		if (pairCollides) collision->collisions.push_back(targetEntity);
	}
}

