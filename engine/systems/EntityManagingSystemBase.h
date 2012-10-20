#pragma once
#include "ThreadedSystemBase.h"

class EntityManagingSystemBase : public ThreadedSystemBase
{
private:
	virtual void pre_frame() {}
	virtual void post_frame() {}
	virtual void on_entity(std::shared_ptr<IEntity> entity) {}

protected:
	std::vector<std::weak_ptr<IEntity>> entities;

public:
	void add_entity(std::weak_ptr<IEntity> new_entity) override;
	void on_wake() final;
};

