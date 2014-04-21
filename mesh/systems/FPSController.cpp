#include <mesh/stdafx.h>
#include <mesh/components.h>
#include <array>
#include "FPSController.h"
using namespace std;
using namespace glm;

string FPSController::description() const
{
    return "Player input";
}

vector<IComponent::ID> FPSController::required_components() const 
{
	return IComponent::require<CInput, CTransform>();
}

vector<ISystem::ID> FPSController::required_systems() const 
{
	return ISystem::require();
}

FPSController::FPSController()
{
	_yclamp = 0;
}

bool FPSController::on_event(SDL_Event& event)
{
    _keyboard.handle(event);
    _mouse.handle(event);

	switch (event.type)
	{
		case SDL_MOUSEMOTION:
		{
			//convert mouse delta to radians, clamping the y-axis to 180 degrees
			coord yrads = event.motion.yrel / (coord)120.0;
			coord xrads = event.motion.xrel / (coord)120.0;
			
			if (_yclamp + yrads > M_PI/2)
				yrads = (coord)M_PI/2 - (_yclamp + yrads);
			if (_yclamp + yrads < -M_PI/2)
				yrads = -((coord)M_PI/2 - (-_yclamp - yrads));
			_yclamp += yrads;

			//rotate around *global* Up, then around *local* Right
			quat pitch(eulers(yrads, 0, 0));
			quat yaw(eulers(0, -xrads, 0));

			for (auto& entity : entities)
			{
				CTransform* xform = entity.lock()->get_component<CTransform>();
				xform->rotate = normalize(yaw * xform->rotate * pitch); 
			}

			//apply the rotation to any existing movement
			_set_velocity();
			return true;
		}

		case SDL_KEYDOWN:
		{
			_set_velocity();
			return true;
		}

		case SDL_KEYUP:
		{
			_set_velocity();
			return true;
		}

		default:
			return false;
	}
}

void FPSController::_set_velocity()
{
	auto character = entities[0].lock();
	auto transform = character->get_component<CTransform>();
	auto velocity = character->get_component<CVelocity>();
	auto input = character->get_component<CInput>();

	vec3 forward = transform->direction_vector();
	auto right = cross(forward, constants::y_axis);
	auto up = cross(right, forward);

	vec3 direction = (coord)_keyboard.get_axis(SDLK_s, SDLK_w) * forward + 
                     (coord)_keyboard.get_axis(SDLK_a, SDLK_d) * right + 
                     (coord)_keyboard.get_axis(SDLK_LSHIFT, SDLK_SPACE) * up;
	if (length(direction) != 0)
		direction = normalize(direction) * input->speed;
	velocity->vector = direction;
}