#pragma once
#include "Identifiable.h"
#include "IComponent.h"

// implementation-agnostic meta-entity class
// a reference to an IEntity constitutes an entity ID
class IEntity
{
public:
	virtual ~IEntity() {}

	//interface
	virtual void        add_component(IComponent::ID type, std::unique_ptr<IComponent> component) = 0;
	virtual void        remove_component(IComponent::ID type) = 0;
	virtual bool        has_component(IComponent::ID type) = 0;
	virtual IComponent* get_component(IComponent::ID type) = 0;
                                                                                     
	//strongly typed convenience methods
	
	template<typename TComponent>
    void add_component(std::unique_ptr<TComponent> component)
    {
		add_component(TComponent::static_id(), std::move(component));
	}

	template<typename TComponent>
    void remove_component()
    {
		erase_component(TComponent::static_id());
	}

	template<typename TComponent>
	bool has_component()
	{
		return has_component(TComponent::static_id());
	}

	template<typename TComponent>
	TComponent* get_component()
	{
		return static_cast<TComponent*>(get_component(TComponent::static_id()));
	}
};

