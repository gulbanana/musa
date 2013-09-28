#include <algorithm>
#include "../framework.h"
#include "EntityManagingSystemBase.h"
using namespace std;

void EntityManagingSystemBase::add_entity(weak_ptr<IEntity> entity)
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

void EntityManagingSystemBase::on_wake()
{
	remove_if(begin(entities), end(entities), [this](weak_ptr<IEntity> entity)	//not sure why "this" is required here- maybe vc++ bug
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