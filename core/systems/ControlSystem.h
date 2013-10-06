#pragma once
#include <core/framework.h>
#include <core/GameState.h>

class ControlSystem : public Identified<ControlSystem, ISystem, ThreadedSystemBase>
{
private:
	GameState* _state;
	virtual void on_wake() final;

public:
	std::vector<ISystem::ID> required_systems() const final;
	ControlSystem(GameState* state);
	bool on_event(SDL_Event& event) override;
};

