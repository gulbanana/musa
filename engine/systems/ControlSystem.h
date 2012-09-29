#pragma once
#include <vector>
#include <typeinfo>
#include <SDL_events.h>
#include "../GameState.h"
#include "ISystem.h"

class ControlSystem : public ISystem
{
	std::shared_ptr<GameState> state;
	SDL_Event event;
public:
	IDENTIFIED(ISystem, Control);
	ControlSystem(std::shared_ptr<GameState> state);
	void on_frame() override;
};

