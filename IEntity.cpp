#include "IEntity.h"
#include <memory>
#include <typeinfo>
#include <algorithm>

using namespace std;

bool IEntity::has_component(string name)
{
	auto result = find_if(components.begin(), components.end(), [&](unique_ptr<IComponent>& comp)
	{
		return name == comp->Name();
	});
	
	return result != components.end();
}

IComponent* IEntity::get_component(string name)
{
	return find_if(components.begin(), components.end(), [&](unique_ptr<IComponent>& comp){ return name == comp->Name(); })->get();
}

void IEntity::add_component(IComponent* new_component)
{
	components.push_back(unique_ptr<IComponent>(new_component));
}