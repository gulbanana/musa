#include "IEntity.h"
#include <typeinfo>
#include <algorithm>

using namespace std;

bool IEntity::has_component(string name)
{
	auto result = find_if(components.begin(), components.end(), [&](shared_ptr<IComponent> comp)
	{
		return name == comp->Name();
	});
	
	return result != components.end();
}

shared_ptr<IComponent> IEntity::get_component(string name)
{
	return *find_if(components.begin(), components.end(), [&](shared_ptr<IComponent> comp){ return name == comp->Name(); });
}