#pragma once
#include <core/framework.h>
#include "ThreadedSystemBase.h"

class EntityManagingSystemBase : public ThreadedSystemBase
{
private:
	virtual std::vector<IComponent::ID> required_components() const = 0;
	
	virtual void on_add(std::shared_ptr<IEntity> entity) {}
	virtual void on_frame_start() {}
	virtual void on_frame_entity(std::shared_ptr<IEntity> entity) {}
	virtual void on_frame_end() {}

protected:
	std::vector<std::weak_ptr<IEntity>> entities;

public:
	void add_entity(std::weak_ptr<IEntity> new_entity) final;
	void on_wake() final;
};

