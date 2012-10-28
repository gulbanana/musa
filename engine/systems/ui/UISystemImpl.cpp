#include <engine/core.h>
#include "UISystemImpl.h"
using namespace std;
using namespace gcn;

UISystemImpl::UISystemImpl(shared_ptr<GameState> s)
{
	_state = s;

	//prepare sdl to be used with guichan
    //XXX these probably aren't being called - no init event
    //and for the keyrepeat one that's a good thing
	SDL_EnableUNICODE(1);
    SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);
	
	//dependency injection
	_gui = make_unique<Gui>();

	_graphics = make_unique<OpenGLGraphics>(800,600);
	_gui->setGraphics(_graphics.get());

	_input = make_unique<SDLInput>();
	_gui->setInput(_input.get());
	
	_fpsLabel = make_unique<Label>("FPS: 00");
	_fpsLabel->setPosition(0, 0);
	_fpsLabel->adjustSize();
	_fpsLabel->setForegroundColor(Color(255, 0, 0));
	_gui->setTop(_fpsLabel.get());
	//Image::setImageLoader
}

void UISystemImpl::on_frame()
{
	_fpsLabel->setCaption("FPS: " + to_string(1000.f / _state->last_frame_time));
	_gui->logic();
	_gui->draw();
}

bool UISystemImpl::on_event(SDL_Event& event)
{
	//on resize, _graphics->setTargetPlane
	_input->pushInput(event);
	return true;
}