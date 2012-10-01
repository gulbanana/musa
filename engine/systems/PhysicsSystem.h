#pragma once
#include <engine/core.h>

class PhysicsSystem : public Identified<ISystem,SYS::Physics>
{
public:
	std::vector<IComponent::ID> required_components() const override;
	void on_entity(std::shared_ptr<IEntity> entity) override;
};

