#pragma once
#include <core/framework.h>
#include <core/GameState.h>
#include "IBlitter.h"

class RenderSystem : public Identified<RenderSystem, ISystem, ThreadedSystemBase>
{
private:
	IBlitter* _blitter;
	std::shared_ptr<GameState> _state;

private:
	std::vector<ISystem::ID> required_systems() const override;
	void on_wake() override;

public:
	RenderSystem(IBlitter*, std::shared_ptr<GameState>);
	~RenderSystem();
};

