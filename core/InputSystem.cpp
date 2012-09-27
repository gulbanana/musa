#include "InputSystem.h"
using namespace std;

vector<string> InputSystem::required_components()
{
	return vector<string>();
}

void InputSystem::on_frame()
{
	sf::Event event;
	while (window->pollEvent(event))
	if (event.type == sf::Event::Closed)
		window->close();
}