#pragma once
#include "IEntityFactory.h"

//produces just-an-id entities
class ManagedEntityFactory final : IEntityFactory
{
private:
	unsigned long long _next;

public:
	ManagedEntityFactory();

	std::unique_ptr<IEntity> create(IArchetype* archetype = nullptr) final;

	void        add_component(unsigned long long entity, IComponent::ID type, std::unique_ptr<IComponent> component);
	void        remove_component(unsigned long long entity, IComponent::ID type);
	bool        has_component(unsigned long long entity, IComponent::ID type);
	IComponent* get_component(unsigned long long entity, IComponent::ID type);
};

