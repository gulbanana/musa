#pragma once
#include <vector>
#include <typeinfo>
#include <engine/GameState.h>
#include "ISystem.h"

class ControlSystem : public ISystem
{
	std::shared_ptr<GameState> state;
public:
	ControlSystem(std::shared_ptr<GameState> state);
	bool on_event(SDL_Event& event) override;
};

