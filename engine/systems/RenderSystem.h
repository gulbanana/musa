#pragma once
#include <engine/core.h>
#include <engine/geometry.h>
#include "EntityManagingSystemBase.h"

class RenderSystem : public Identified<ISystem,SYS::Render,EntityManagingSystemBase>
{
	std::unique_ptr<IRenderer> _renderer;

	void pre_frame() override;
	void post_frame() override;
	void on_entity(std::shared_ptr<IEntity> entity) override;
	bool on_event(SDL_Event& event) override;

public:
	RenderSystem(std::unique_ptr<IRenderer>);

	std::vector<IComponent::ID> required_components() const override;
	virtual std::vector<ISystem::ID> required_systems() const override;
};

