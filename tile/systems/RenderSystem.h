#pragma once
#include <core/framework.h>
#include <core/GameState.h>
#include "IBlitter.h"

class RenderSystem : public Identified<RenderSystem, ISystem, EntityManagingSystemBase>
{
private:
	IBlitter* _blitter;
	std::shared_ptr<GameState> _state;
    grid* _tram;

private:
	std::vector<ISystem::ID> required_systems() const override;
    std::vector<IComponent::ID> required_components() const override;
    void on_frame_start() override;
    void on_frame_entity(std::shared_ptr<IEntity>) override;

public:
	RenderSystem(IBlitter*, std::shared_ptr<GameState>);
	~RenderSystem();
};

