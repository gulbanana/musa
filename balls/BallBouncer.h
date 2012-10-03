#pragma once
#include <engine/core.h>
#include <engine/geometry.h>

class BallBouncer : public Identified<ISystem,ISystem::ID::Logic>
{
private:
	coord _width;
	coord _height;
	virtual void on_entity(std::shared_ptr<IEntity> entity) override;
	virtual bool on_event(SDL_Event&) override;
public:
	BallBouncer(int x, int y);
	virtual std::vector<IComponent::ID> required_components() const override;
	virtual std::vector<ISystem::ID> required_systems() const override;
};

