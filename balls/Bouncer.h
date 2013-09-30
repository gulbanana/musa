#pragma once
#include <core/framework.h>
#include <mesh/types.h>

class Bouncer : public Identified<Bouncer,ISystem,EntityManagingSystemBase>
{
private:
	virtual std::vector<IComponent::ID> required_components() const override;
	virtual std::vector<ISystem::ID> required_systems() const override;

	virtual void on_frame_entity(std::shared_ptr<IEntity> entity) override;

protected:
	coord _width;
	coord _height;
	coord _depth;

public:
	Bouncer(int r);
	Bouncer(int x, int y, int z);
};

