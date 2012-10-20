#pragma once
#include <engine/GameState.h>
#include <engine/systems/EntityManagingSystemBase.h>

class FPSController : public Identified<ISystem,SYS::Control,EntityManagingSystemBase>
{
private:
	std::shared_ptr<GameState> _state;
	bool _firstMouse;

public:
	std::vector<IComponent::ID> required_components() const override;
	std::vector<ISystem::ID> required_systems() const override;
	FPSController();
	bool on_event(SDL_Event& event) override;
};

