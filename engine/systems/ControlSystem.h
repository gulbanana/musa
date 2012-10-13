#pragma once
#include <vector>
#include <typeinfo>
#include <engine/core.h>
#include <engine/GameState.h>

class ControlSystem : public Identified<ISystem,SYS::Control>
{
private:
	std::shared_ptr<GameState> _state;
	
public:
	ControlSystem(std::shared_ptr<GameState> state);
	bool on_event(SDL_Event& event) override;
};

