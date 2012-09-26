#pragma once
#include <SFML/Graphics.hpp>
#include "ISystem.h"

class RenderSystem : public ISystem
{
	sf::RenderTarget* surface;

public:
	RenderSystem(sf::RenderTarget* s) : surface(s) {}

	void frame() override;
	std::vector<std::string> required_components() override;
};

