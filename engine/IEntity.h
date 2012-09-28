#pragma once
#include <memory>
#include <map>
#include "IComponent.h"

//	IEntity contract:
//	component pointers remain valid until destruction, so holding ownership of the entity means you can use a pointer acquired earlier
class IEntity
{
protected:
	std::map<CID, std::unique_ptr<IComponent>> components;
	IEntity() {}
	template<typename TComponent> void add_component(std::unique_ptr<TComponent> newComponent)
	{
		components[TComponent::ID] = std::move(newComponent);
	}

public:
	template<typename TComponent> inline bool has_component()
	{
		return has_component(TComponent::ID);
	}

	bool has_component(CID id)
	{
		return components.count(id) > 0;
	}

	template<typename TComponent> TComponent* get_component()
	{
		return static_cast<TComponent*>(components[TComponent::ID].get());
	}
};

