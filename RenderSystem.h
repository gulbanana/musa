#pragma once
#include <SFML/Graphics.hpp>
#include "ISystem.h"

class RenderSystem : public ISystem
{
	sf::Font font;
	sf::RenderTarget* surface;

public:
	RenderSystem(sf::RenderTarget* s);

	void frame() override;
	std::vector<std::string> required_components() override;
};

