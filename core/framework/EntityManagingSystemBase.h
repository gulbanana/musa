#pragma once
#include "ThreadedSystemBase.h"

//Base class for systems which manage all entities with a specific component.
//To use, override required_components() and required_systems() as well as
//some events.
class EntityManagingSystemBase : public ThreadedSystemBase
{
private:
	void on_entity(std::weak_ptr<IEntity> new_entity) override final;
	void on_wake() override final;

	virtual std::vector<IComponent::ID> required_components() const = 0;
	virtual void on_add(std::shared_ptr<IEntity> entity) {}
	virtual void on_frame_start() {}
	virtual void on_frame_entity(std::shared_ptr<IEntity> entity) {}
	virtual void on_frame_end() {}

protected:
	std::vector<std::weak_ptr<IEntity>> entities;
};

