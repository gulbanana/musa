#include <scape/stdafx.h>
#include <tile/components.h>
#include <scape/components.h>
#include "PadControlSystem.h"
using namespace std;

string PadControlSystem::description() const
{
    return "Gamepad input manager";
}

vector<ISystem::ID> PadControlSystem::required_systems() const
{
	return ISystem::require();
}

std::vector<IComponent::ID> PadControlSystem::required_components() const
{
    return IComponent::require<CPadInput, CVelocity>();
}

PadControlSystem::PadControlSystem(GameState* state) : 
_state(state), _controller(nullptr), _deadzone(5000.f), _speed(15.f)
{
    for (int i = 0; i < SDL_NumJoysticks(); i++)
        platform->println("controller " + to_string(i) + ": " + SDL_GameControllerNameForIndex(i));

    if (SDL_NumJoysticks() > 0)
        _controller = SDL_GameControllerOpen(0);
}

PadControlSystem::~PadControlSystem() 
{
    if (_controller != nullptr)
        SDL_GameControllerClose(_controller);
}

bool PadControlSystem::on_event(SDL_Event& event)
{
    return false;
}

void PadControlSystem::on_frame_start()
{
    if (_controller != nullptr)
    {
        if (SDL_GameControllerGetButton(_controller, SDL_CONTROLLER_BUTTON_START))
        {
            _state->shouldQuit = true;
        }
    }
}

void PadControlSystem::on_frame_entity(shared_ptr<IEntity> e)
{
    if (_controller != nullptr)
    {
        auto velocity = e->get_component<CVelocity>();

        auto x = (float)SDL_GameControllerGetAxis(_controller, SDL_CONTROLLER_AXIS_LEFTX);
        auto y = -(float)SDL_GameControllerGetAxis(_controller, SDL_CONTROLLER_AXIS_LEFTY);

        auto w_e = (abs(x) > _deadzone) ? vec2(x, 0) : vec2(0, 0);
        auto s_n = (abs(y) > _deadzone) ? vec2(0, y) : vec2(0, 0);

        //platform->println("w_e: " + to_string(w_e));
        //platform->println("s_n: " + to_string(s_n));

        velocity->vector = (w_e + s_n) / 32767.f * _speed;
    }
}