#include <engine/core.h>
#include "AutonomousEntity.h"
using namespace std;

AutonomousEntity::AutonomousEntity()
{
}

void AutonomousEntity::add_component(IComponent::ID type, unique_ptr<IComponent> component)
{
	_components[type] = std::move(component);
}

void AutonomousEntity::remove_component(IComponent::ID type)
{
	_components.erase(type);
}

bool AutonomousEntity::has_component(IComponent::ID type)
{
	return _components.count(type) == 1;
}

IComponent* AutonomousEntity::get_component(IComponent::ID type)
{
	return _components[type].get();
}