#pragma once
#include <engine/core.h>
#include <engine/geometry.h>
#include <engine/systems/EntityManagingSystemBase.h>

class BallBouncer : public Identified<ISystem,ISystem::ID::Logic,EntityManagingSystemBase>
{
private:
	coord _width;
	coord _height;
	coord _depth;

	virtual void on_entity(std::shared_ptr<IEntity> entity) override;
	virtual bool on_event(SDL_Event&) override;

public:
	BallBouncer(int r);
	BallBouncer(int x, int y, int z);

	virtual std::vector<IComponent::ID> required_components() const override;
	virtual std::vector<ISystem::ID> required_systems() const override;
};

