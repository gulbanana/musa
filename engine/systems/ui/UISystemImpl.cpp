#include "UISystemImpl.h"
using namespace std;

UISystemImpl::UISystemImpl(shared_ptr<GameState> s)
{
	_state = s;
}

void UISystemImpl::on_frame()
{
	print("FPS: " + to_string(_state->fps), 0, 0);
}

bool UISystemImpl::on_event(SDL_Event& event)
{
	return false;
}

void UISystemImpl::print(string output, float x, float y)
{
}