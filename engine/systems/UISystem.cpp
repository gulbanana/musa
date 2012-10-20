#include <engine/core.h>
#include <array>
#include "UISystem.h"
#include "ui/UISystemImpl.h"
using namespace std;

vector<CMP> UISystem::required_components() const 
{
	array<CMP,0> compTypes = {};
	return vector<CMP>(compTypes.begin(), compTypes.end());
}

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