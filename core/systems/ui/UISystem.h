#pragma once
#include <core/framework.h>
#include <core/GameState.h>

class UISystemImpl;

class UISystem : public Identified<ISystem,SYS::UI,ThreadedSystemBase>
{
	UISystemImpl* _pimpl;
public:
	UISystem(std::shared_ptr<GameState> s);

	std::vector<ISystem::ID> required_systems() const final;

	void on_wake() override;
	bool on_event(SDL_Event& event) override;
};

