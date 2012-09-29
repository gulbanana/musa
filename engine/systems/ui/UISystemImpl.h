#pragma once
#include <memory>
#include <string>
#include <engine/GameState.h>
#include <SDL_events.h>
#include <guichan/guichan.hpp>

class UISystemImpl
{
	std::shared_ptr<GameState> _state;
	void print(std::string output, float x, float y);
public:
	UISystemImpl(std::shared_ptr<GameState> s);
	void on_frame();
	bool on_event(SDL_Event& event);
};
