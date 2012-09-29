#include "ControlSystem.h"
using namespace std;

ControlSystem::ControlSystem(std::shared_ptr<GameState> s) : state(s)
{
}

void ControlSystem::on_frame()
{
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				state->shouldQuit = true;
				break;
		}
	}
}