#pragma once
#include "IComponent.h"
#include "IEntity.h"

class AutonomousEntityFactory;

// entity implementation which stores its components in a local list
class AutonomousEntity final : IEntity
{
	friend class AutonomousEntityFactory;

private:
	std::map<IComponent::ID, std::unique_ptr<IComponent>> _components;

	AutonomousEntity();

protected:
	void        add_component(IComponent::ID type, std::unique_ptr<IComponent> component) final;
	void        remove_component(IComponent::ID type) final;
	bool        has_component(IComponent::ID type) final;
	IComponent* get_component(IComponent::ID type) final;
};

