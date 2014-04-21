#include <core/stdafx.h>
#include "ControlSystem.h"
using namespace std;

vector<ISystem::ID> ControlSystem::required_systems() const 
{
	return require();
}

ControlSystem::ControlSystem(GameState* state) : _state(state) {}

bool ControlSystem::on_event(SDL_Event& event)
{
	switch (event.type)
	{
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE)
			{
				_state->shouldQuit = true;
				return true;
			}
			return false;

		case SDL_QUIT:
			_state->shouldQuit = true;
			return true;

		default:
			return false;
	}
}

void ControlSystem::on_frame() 
{
}