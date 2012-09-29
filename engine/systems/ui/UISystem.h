#pragma once
#include <engine/GameState.h>
#include "../ISystem.h"

class UISystemImpl;

class UISystem : public ISystem
{
	UISystemImpl* _pimpl;
public:
	UISystem(std::shared_ptr<GameState> s);
	void on_frame() override;
	bool on_event(SDL_Event& event) override;
};

