#pragma once
#include <vector>
#include <typeinfo>
#include <engine/core.h>
#include <engine/GameState.h>

class ControlSystem : public ISystem
{
	std::shared_ptr<GameState> state;
public:
	ControlSystem(std::shared_ptr<GameState> state);
	bool on_event(SDL_Event& event) override;
};

