#pragma once
#include <core/framework.h>
#include <mesh/types.h>

class Bouncer : public Identified<Bouncer,ISystem,EntityManagingSystemBase>
{
protected:
	coord _width;
	coord _height;
	coord _depth;

public:
    std::string description() const override;
    virtual std::vector<IComponent::ID> required_components() const override;
    virtual std::vector<ISystem::ID> required_systems() const override;

	Bouncer(int r);
	Bouncer(int x, int y, int z);

    virtual void on_frame_entity(std::shared_ptr<IEntity> entity) override;
};

