#pragma once
#include <memory>
#include <vector>
#include "IComponent.h"

class IEntity
{
protected:
	IEntity() {}
	std::vector<std::shared_ptr<IComponent>> components;

public:
	bool has_component(std::string name);
	template<typename TComponent> std::shared_ptr<TComponent> get_component();
};

