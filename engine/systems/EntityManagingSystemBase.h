#pragma once
#include <engine/core.h>

class EntityManagingSystemBase : public ISystem
{
private:
	virtual void pre_frame() {}
	virtual void post_frame() {}
	virtual void on_entity(std::shared_ptr<IEntity> entity) {}

protected:
	std::vector<std::weak_ptr<IEntity>> entities;

public:
	virtual void add_entity(std::weak_ptr<IEntity> new_entity) override;
	virtual void on_frame() override;
};

