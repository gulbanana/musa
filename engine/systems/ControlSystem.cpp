#include "ControlSystem.h"
using namespace std;

ControlSystem::ControlSystem(std::shared_ptr<GameState> s) : state(s)
{
}

bool ControlSystem::on_event(SDL_Event& event)
{
	switch (event.type)
	{
		case SDL_QUIT:
			state->shouldQuit = true;
			return true;

		default:
			return false;
	}
}