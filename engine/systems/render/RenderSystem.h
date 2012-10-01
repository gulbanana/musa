#pragma once
#include <engine/systems/ISystem.h>

class RenderSystem : public ISystem
{
public:
	RenderSystem(int width, int height);
	~RenderSystem();

	std::vector<IComponent::ID> required_components() override;
	void on_entity(std::shared_ptr<IEntity> entity) override;
	void on_frame() override;
	void on_post_frame() override;
	bool on_event(SDL_Event& event) override;
};

