#pragma once
#include <engine/GameState.h>
#include "ThreadedSystemBase.h"

class ControlSystem : public Identified<ISystem,SYS::Control,ThreadedSystemBase>
{
private:
	std::shared_ptr<GameState> _state;
	virtual void on_wake() final;

public:
	std::vector<IComponent::ID> required_components() const final;
	std::vector<ISystem::ID> required_systems() const final;
	ControlSystem(std::shared_ptr<GameState> state);
	bool on_event(SDL_Event& event) override;
};

