#pragma once
#include <core/GameState.h>
#include <core/framework.h>
#include <core/input.h>

class FPSController : public Identified<FPSController, ISystem, EntityManagingSystemBase>
{
private:
	std::shared_ptr<GameState> _state;

    KeyboardController _keyboard;
    CapturedMouseController _mouse;

    coord _yclamp;

	coord _calc_lr();
	coord _calc_fb();
	coord _calc_ud();
	void _set_velocity();

public:
	std::vector<IComponent::ID> required_components() const override;
	std::vector<ISystem::ID> required_systems() const override;
	FPSController();
	bool on_event(SDL_Event& event) override;
};

