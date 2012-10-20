#pragma once
#include "IEntity.h"

class ManagedEntityFactory;

// entity implementation which stores its components in its global factory
class ManagedEntity final : IEntity
{
	friend class ManagedEntityFactory;

private:
	unsigned long long _id;
	ManagedEntityFactory* _factory;
	ManagedEntity(unsigned long long id, ManagedEntityFactory* factory);

protected:
	void        add_component(IComponent::ID type, std::unique_ptr<IComponent> component) final;
	void        remove_component(IComponent::ID type) final;
	bool        has_component(IComponent::ID type) final;
	IComponent* get_component(IComponent::ID type) final;
};

