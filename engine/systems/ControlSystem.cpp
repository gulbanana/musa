#include "ControlSystem.h"
using namespace std;

ControlSystem::ControlSystem(std::shared_ptr<GameState> s) : _state(s)
{
	SDL_EnableKeyRepeat(1, 0);
}

bool ControlSystem::on_event(SDL_Event& event)
{
	switch (event.type)
	{
		case SDL_QUIT:
			_state->shouldQuit = true;
			return true;

		default:
			return false;
	}
}