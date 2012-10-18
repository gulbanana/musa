#pragma once
#include <engine/GameState.h>
#include <SDL_events.h>
#include <guichan/guichan.hpp>
#include <guichan/sdl/sdlinput.hpp>
#include <guichan/opengl/openglgraphics.hpp>

class UISystemImpl
{
	std::shared_ptr<GameState> _state;

	//guichan objects
	std::unique_ptr<gcn::Gui> _gui;
	std::unique_ptr<gcn::SDLInput> _input;
	std::unique_ptr<gcn::OpenGLGraphics> _graphics;
	
	//the entire gui!
	std::unique_ptr<gcn::Label> _fpsLabel;

	//pimpl passthrough
public:
	UISystemImpl(std::shared_ptr<GameState> s);
	void on_frame();
	bool on_event(SDL_Event& event);
};
