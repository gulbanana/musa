#include <engine/core.h>
#include "UISystem.h"
#include "ui/UISystemImpl.h"
using namespace std;

vector<SYS> UISystem::required_systems() const 
{
	array<SYS,1> sysTypes = {SYS::Render};
	return vector<SYS>(sysTypes.begin(), sysTypes.end());
}

UISystem::UISystem(shared_ptr<GameState> s) : _pimpl(new UISystemImpl(s)) {}

void UISystem::on_wake()
{
	_pimpl->on_frame();
}

bool UISystem::on_event(SDL_Event& event)
{
	return _pimpl->on_event(event);
}