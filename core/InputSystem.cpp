#include "InputSystem.h"
using namespace std;

void InputSystem::on_frame()
{
	sf::Event event;
	while (window->pollEvent(event))
	if (event.type == sf::Event::Closed)
		window->close();
}