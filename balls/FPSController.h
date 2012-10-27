#pragma once
#include <engine/GameState.h>
#include <engine/systems/EntityManagingSystemBase.h>
#include <set>

class FPSController : public Identified<ISystem,SYS::Control,EntityManagingSystemBase>
{
private:
	std::shared_ptr<GameState> _state;
	bool _firstMouse;
	std::set<SDLKey> _keys;
	coord _yclamp;

	bool _key(SDLKey);
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

