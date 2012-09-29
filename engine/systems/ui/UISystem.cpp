#include "UISystem.h"
#include "UISystemImpl.h"
using namespace std;

UISystem::UISystem(shared_ptr<GameState> s) : _pimpl(new UISystemImpl(s)) {}

void UISystem::on_frame()
{
	_pimpl->on_frame();
}

bool UISystem::on_event(SDL_Event& event)
{
	return _pimpl->on_event(event);
}