#include <core/stdafx.h>
#include "EntityManagingSystemBase.h"
using namespace std;

void EntityManagingSystemBase::on_entity(weak_ptr<IEntity> entity)
{ 
	auto const& comps = required_components();
	auto owned = entity.lock();

	auto matches = count_if(comps.begin(), comps.end(), [&](IComponent::ID requirement)
	{
		return owned->has_component(requirement);
	});

	if (matches == comps.size())
		entities.push_back(entity); 
}

void EntityManagingSystemBase::on_frame()
{
	remove_if(begin(entities), end(entities), [](weak_ptr<IEntity> entity)
	{
		return entity.expired();
	});

	on_frame_start();

	for (auto weakEntity : entities)
	{
		on_frame_entity(weakEntity.lock());
	}

	on_frame_end();
}