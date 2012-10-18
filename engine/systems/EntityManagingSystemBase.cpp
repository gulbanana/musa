#include <engine/core.h>
#include <algorithm>
#include "EntityManagingSystemBase.h"
using namespace std;

void EntityManagingSystemBase::add_entity(weak_ptr<IEntity> new_entity)
{ 
	entities.push_back(new_entity); 
}

void EntityManagingSystemBase::on_frame()
{
	remove_if(begin(entities), end(entities), [this](weak_ptr<IEntity> entity)	//not sure why "this" is required here- maybe vc++ bug
	{
		return entity.expired();
	});

	pre_frame();

	for (auto weakEntity : entities)
	{
		on_entity(weakEntity.lock());
	}

	post_frame();
}