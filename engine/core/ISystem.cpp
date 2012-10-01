#include <algorithm>
#include "ISystem.h"
using namespace std;

std::vector<ISystem::ID> ISystem::required_systems() const
{ 
	return std::vector<ISystem::ID>(); 
}

std::vector<IComponent::ID> ISystem::required_components() const
{ 
	return std::vector<IComponent::ID>(); 
}

bool ISystem::event(SDL_Event& event) 
{ 
	return on_event(event); 
}

void ISystem::add_entity(weak_ptr<IEntity> new_entity)
{ 
	entities.push_back(new_entity); 
}

void ISystem::frame()
{
	remove_if(begin(entities), end(entities), [](weak_ptr<IEntity> entity)
	{
		return entity.expired();
	});

	on_frame();

	for (auto entity : entities)
	{
		on_entity(entity.lock());
	}

	on_post_frame();
}

bool ISystem::operator<(ISystem const& rhs)
{
	auto sids = rhs.required_systems();
	return (find(sids.begin(), sids.end(), _id()) != sids.end());
}