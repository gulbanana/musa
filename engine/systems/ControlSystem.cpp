#include <engine/core.h>
#include <array>
#include "ControlSystem.h"
using namespace std;

vector<CMP> ControlSystem::required_components() const 
{
	array<CMP,0> compTypes = {};
	return vector<CMP>(compTypes.begin(), compTypes.end());
}

vector<SYS> ControlSystem::required_systems() const 
{
	array<SYS,0> sysTypes = {};
	return vector<SYS>(sysTypes.begin(), sysTypes.end());
}

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

void ControlSystem::on_wake() 
{
}