#pragma once
#include <vector>
#include <typeinfo>
#include <SFML/Graphics.hpp>
#include "ISystem.h"

class InputSystem : public ISystem
{
	sf::RenderWindow* window;

public:
	InputSystem(sf::RenderWindow* s) : window(s) {}

	std::vector<std::string> required_components() override;
	void on_frame() override;
};

