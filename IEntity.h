#pragma once
#include <memory>
#include <vector>
#include "IComponent.h"

//	IEntity contract:
//	component pointers remain valid until destruction, so holding ownership of the entity means you can use a pointer acquired earlier
class IEntity
{
protected:
	std::vector<std::unique_ptr<IComponent>> components;
	IEntity() {}
	void add_component(IComponent* component);

public:
	bool has_component(std::string name);
	IComponent* get_component(std::string name);
};

