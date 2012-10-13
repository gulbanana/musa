#pragma once
#include <engine/core.h>
#include <engine/geometry.h>
#include <engine/systems/EntityManagingSystemBase.h>

class Bouncer : public Identified<ISystem,ISystem::ID::Logic,EntityManagingSystemBase>
{
private:
	virtual void on_entity(std::shared_ptr<IEntity> entity) override;

protected:
	coord _width;
	coord _height;
	coord _depth;

public:
	Bouncer(int r);
	Bouncer(int x, int y, int z);

	virtual std::vector<IComponent::ID> required_components() const override;
	virtual std::vector<ISystem::ID> required_systems() const override;
};

