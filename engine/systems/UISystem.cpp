#include <array>
#include <vector>
#include "UISystem.h"
using namespace std;

UISystem::UISystem(shared_ptr<GameState> s) : state(s)
{
	//load fonts..?
}

void UISystem::on_frame()
{
	print("FPS: " + to_string(state->fps), 0, 0);
}

void UISystem::print(string output, float x, float y)
{
	//gltext
}