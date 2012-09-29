#include <array>
#include <vector>
#include "UISystem.h"
using namespace std;

UISystem::UISystem(int& fpsCounter) : fps(fpsCounter)
{
	//load fonts..?
}

void UISystem::on_frame()
{
	print("FPS: " + to_string(fps), 0, 0);
}

void UISystem::print(string output, float x, float y)
{
	//gltext
}