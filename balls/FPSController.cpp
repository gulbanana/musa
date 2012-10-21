#include <engine/core.h>
#include <engine/components.h>
#include "FPSController.h"
using namespace std;

vector<CMP> FPSController::required_components() const 
{
	array<CMP,2> compTypes = {CMP::Input, CMP::Transform};
	return vector<CMP>(compTypes.begin(), compTypes.end());
}

vector<SYS> FPSController::required_systems() const 
{
	array<SYS,0> sysTypes = {};
	return vector<SYS>(sysTypes.begin(), sysTypes.end());
}

FPSController::FPSController()
{
	_firstMouse = true;
}

bool FPSController::on_event(SDL_Event& event)
{
	auto character = entities[0].lock();
	auto position = character->get_component<CTransform>();
	auto player = character->get_component<CInput>();

	switch (event.type)
	{
		case SDL_MOUSEMOTION:
			if (_firstMouse)
			{
				_firstMouse = false;
				return true;
			}

			position->rotate = glm::rotate(position->rotate, event.motion.xrel / 5, maths::y_axis);
			position->rotate = glm::rotate(position->rotate, event.motion.yrel / 5, -maths::x_axis);
			return true;

		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_w)
			{
				position->translate.z -= player->speed;
				return true;
			}
			else if (event.key.keysym.sym == SDLK_a)
			{
				position->translate.x += player->speed;
				return true;
			}
			else if (event.key.keysym.sym == SDLK_s)
			{
				position->translate.z += player->speed;
				return true;
			}
			else if (event.key.keysym.sym == SDLK_d)
			{
				position->translate.x -= player->speed;
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