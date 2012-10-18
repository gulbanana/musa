#pragma once
#include <engine/GameState.h>

class UISystemImpl;

class UISystem : public Identified<ISystem,SYS::UI>
{
	UISystemImpl* _pimpl;
public:
	UISystem(std::shared_ptr<GameState> s);

	virtual std::vector<ISystem::ID> required_systems() const override;

	void on_frame() override;
	bool on_event(SDL_Event& event) override;
};

