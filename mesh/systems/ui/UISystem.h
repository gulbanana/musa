#pragma once
#include <core/framework.h>
#include <core/GameState.h>

class UISystemImpl;

class UISystem : public Identified<UISystem,ISystem>
{
	UISystemImpl* _pimpl;
public:
	UISystem(GameState* s);

	std::vector<ISystem::ID> required_systems() const final;

	void on_frame() override;
	bool on_event(SDL_Event& event) override;
};

