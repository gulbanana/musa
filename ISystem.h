#pragma once
#include <memory>
#include <vector>
#include <string>
#include <typeinfo>
#include "IEntity.h"

class ISystem
{
protected:
	std::vector<std::weak_ptr<IEntity>> entities;

public:
	virtual ~ISystem() {}
	virtual std::vector<std::string> required_components() = 0;
	virtual void frame() = 0;

	void add_entity(std::weak_ptr<IEntity> new_entity) { entities.push_back(new_entity); }
};

