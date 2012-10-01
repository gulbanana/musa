#pragma once
#include <engine/core.h>
#include <engine/geometry.h>

class RenderSystem : public Identified<ISystem,SYS::Render>
{
	std::unique_ptr<IRenderer> _renderer;
public:
	RenderSystem(std::unique_ptr<IRenderer>);

	std::vector<IComponent::ID> required_components() const override;
	virtual std::vector<ISystem::ID> required_systems() const override;

	void on_entity(std::shared_ptr<IEntity> entity) override;
	void on_frame() override;
	void on_post_frame() override;
	bool on_event(SDL_Event& event) override;
};

