#pragma once
#include <memory>
#include <vector>
#include "IComponent.h"

class IEntity
{
protected:
	std::vector<std::shared_ptr<IComponent>> components;
	IEntity() {}

public:
	bool has_component(std::string name);
	std::shared_ptr<IComponent> get_component(std::string name);
};

