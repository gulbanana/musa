#include "IEntity.h"
#include <typeinfo>
#include <algorithm>

using namespace std;

template<typename TComponent>
shared_ptr<TComponent> IEntity::get_component()
{
	auto result = find_if(components.begin(), components.end(), [](shared_ptr<IComponent> comp)
	{
		return typeid(*comp.get()) == typeid(TComponent);
	});
	
	return *result;
}

bool IEntity::has_component(string name)
{
	auto result = find_if(components.begin(), components.end(), [&](shared_ptr<IComponent> comp)
	{
		return typeid(*comp.get()).raw_name() == name;
	});
	
	return result != components.end();
}