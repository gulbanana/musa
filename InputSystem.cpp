#include "InputSystem.h"
using namespace std;

void InputSystem::frame()
{
	sf::Event event;
	while (window->pollEvent(event))
	if (event.type == sf::Event::Closed)
		window->close();
}

vector<string> InputSystem::required_components()
{
	return vector<string>();
}