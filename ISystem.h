#pragma once
#include <memory>
#include <vector>
#include <string>
#include <typeinfo>
#include "IEntity.h"

class ISystem
{
	virtual void on_frame() {}
	virtual void on_entity(std::shared_ptr<IEntity> entity) {}

protected:
	std::vector<std::weak_ptr<IEntity>> entities;

public:
	virtual ~ISystem() {}
	virtual std::vector<std::string> required_components() = 0;

	void add_entity(std::weak_ptr<IEntity> new_entity);
	void frame();
};

