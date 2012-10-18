#include <engine/core.h>
#include <engine/components.h>
#include "FPSController.h"
using namespace std;

vector<CMP> FPSController::required_components() const 
{
	array<CMP,2> compTypes = {CMP::Player, CMP::Position};
	return vector<CMP>(compTypes.begin(), compTypes.end());
}

FPSController::FPSController()
{
	_firstMouse = true;
}

bool FPSController::on_event(SDL_Event& event)
{
	auto character = entities[0].lock();
	auto position = character->get_component<CPosition>();
	auto player = character->get_component<CPlayer>();

	switch (event.type)
	{
		case SDL_MOUSEMOTION:
			if (_firstMouse)
			{
				_firstMouse = false;
				return true;
			}

			position->orientation.y += event.motion.xrel / 5;
			position->orientation.x += event.motion.yrel / 5;
			return true;

		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_w)
			{
				position->location.z -= player->speed;
				return true;
			}
			else if (event.key.keysym.sym == SDLK_a)
			{
				position->location.x += player->speed;
				return true;
			}
			else if (event.key.keysym.sym == SDLK_s)
			{
				position->location.z += player->speed;
				return true;
			}
			else if (event.key.keysym.sym == SDLK_d)
			{
				position->location.x -= player->speed;
				return true;
			}
			else
			{
				return false;
			}

		default:
			return false;
	}
}