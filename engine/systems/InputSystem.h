#pragma once
#include <vector>
#include <typeinfo>
#include <SFML/Window.hpp>
#include "ISystem.h"

class InputSystem : public ISystem
{
	sf::Window* window;

public:
	InputSystem(sf::Window* s) : window(s) {}
	void on_frame() override;
};

