#pragma once
#include <engine/core.h>

class PhysicsSystem : public ISystem
{
public:
	std::vector<IComponent::ID> required_components() override;
	void on_entity(std::shared_ptr<IEntity> entity) override;
};

