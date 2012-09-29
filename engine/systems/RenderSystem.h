#pragma once
#include "ISystem.h"

class RenderSystem : public ISystem
{
public:
	RenderSystem();
	~RenderSystem();

	std::vector<IComponent::ID> required_components() override;
	void on_frame() override;
	void on_entity(std::shared_ptr<IEntity> entity) override;
};

