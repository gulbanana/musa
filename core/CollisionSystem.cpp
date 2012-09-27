#include <array>
#include <iterator>
#include <typeinfo>
#include <tuple>
#include "misc.h"
#include "CPosition2D.h"
#include "CShapeGeometry.h"
#include "CCollision.h"
#include "CollisionSystem.h"
#include "RectIntersectionDetector.h"
using namespace std;

vector<CID> CollisionSystem::required_components()
{
	array<CID,3> compTypes = {CID::Position2D, CID::ShapeGeometry, CID::Collision};
	return vector<CID>(compTypes.begin(), compTypes.end());
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
	auto geometry = sourceEntity->get_component<CShapeGeometry>();

	collision->collisions.clear();

	for_each(begin(targets), end(targets), [&](weak_ptr<IEntity>& entity)
	{
		auto targetEntity = entity.lock();
		if (sourceEntity.get() == targetEntity.get()) return;

		auto pairCollides = true;

		for_each(begin(detectors), end(detectors), [&](unique_ptr<ICollisionDetector>& detector)
		{
			pairCollides = detector->collide(sourceEntity, targetEntity);
			if (!pairCollides) return;
		});
		
		if (pairCollides) collision->collisions.push_back(targetEntity);
	});
}

