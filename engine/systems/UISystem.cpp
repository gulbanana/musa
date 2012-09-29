#include <array>
#include <vector>
#include "UISystem.h"
using namespace std;

UISystem::UISystem(sf::Font f, sf::RenderTarget* s, int& fpsCounter) : font(f), surface(s), fps(fpsCounter)
{
	text = sf::Text("", font);
	text.setColor(sf::Color::Red);
}

void UISystem::on_frame()
{
	print("FPS: " + to_string(fps), 0, 0);
}

void UISystem::print(string output, float x, float y)
{
	text.setString(output);
	text.setPosition(x, y);

	surface->draw(text);
}