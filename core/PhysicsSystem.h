#pragma once
#include "ISystem.h"

class PhysicsSystem : public ISystem
{
public:
	std::vector<CID> required_components() override;
	void on_entity(std::shared_ptr<IEntity> entity) override;
};

