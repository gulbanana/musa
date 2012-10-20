#include "engine/core.h"
#include "ManagedEntity.h"
using namespace std;

ManagedEntity::ManagedEntity(unsigned long long id, ManagedEntityFactory* factory)
{
	_id = id;
	_factory = factory;
}

void ManagedEntity::add_component(IComponent::ID type, unique_ptr<IComponent> component)
{
	_factory->add_component(_id, type, move(component));
}

void ManagedEntity::remove_component(IComponent::ID type)
{
	_factory->remove_component(_id, type);
}

bool ManagedEntity::has_component(IComponent::ID type)
{
	return _factory->has_component(_id, type);
}

IComponent* ManagedEntity::get_component(IComponent::ID type)
{
	return _factory->get_component(_id, type);
}