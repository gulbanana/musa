#pragma once
#include <engine/core.h>
class BallBouncer : public ISystem
{
private:
	virtual void on_entity(std::shared_ptr<IEntity> entity) override;
public:
	virtual std::vector<IComponent::ID> required_components() override;
};

