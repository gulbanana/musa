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
	auto transform = character->get_component<CTransform>();
	auto velocity = character->get_component<CVelocity>();
	auto input = character->get_component<CInput>();

	switch (event.type)
	{
		case SDL_MOUSEMOTION:
			if (_firstMouse)
			{
				_firstMouse = false;
				return true;
			}

			transform->rotate = glm::rotate(transform->rotate, event.motion.xrel / (coord)4.0, maths::y_axis);
			transform->rotate = glm::rotate(transform->rotate, event.motion.yrel / (coord)4.0, -maths::x_axis);
			return true;

		case SDL_KEYDOWN:
			_keys.insert(event.key.keysym.sym);
			velocity->vector.x = _calc_lr(input->speed);
			velocity->vector.z = _calc_fb(input->speed);
			velocity->vector.y = _calc_ud(input->speed);
			return true;

		case SDL_KEYUP:
			_keys.erase(event.key.keysym.sym);
			velocity->vector.x = _calc_lr(input->speed);
			velocity->vector.z = _calc_fb(input->speed);
			velocity->vector.y = _calc_ud(input->speed);
			return true;

		default:
			return false;
	}
}

bool FPSController::_key(SDLKey k)
{
	return _keys.find(k) != _keys.end();
}

coord FPSController::_calc_lr(coord speed)
{
	coord result = 0;

	if (_key(SDLK_a))
		result += speed;
	if (_key(SDLK_d))
		result -= speed;

	return result;
}

coord FPSController::_calc_fb(coord speed)
{
	coord result = 0;

	if (_key(SDLK_w))
		result -= speed;
	if (_key(SDLK_s))
		result += speed;

	return result;
}

coord FPSController::_calc_ud(coord speed)
{
	coord result = 0;
	if (_key(SDLK_SPACE))
		result += speed;
	if (_key(SDLK_LSHIFT))
		result -= speed;

	return result;
}