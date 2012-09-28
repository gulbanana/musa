#pragma once
#include <SFML/Graphics.hpp>
#include "ISystem.h"

class UIRenderSystem : public ISystem
{
	sf::Font font;
	sf::Text text;
	sf::RenderTarget* surface;

	//UI information
	int& fps;

	void print(std::string output, float x, float y);

public:
	UIRenderSystem(sf::Font uiFont, sf::RenderTarget* s, int& fpsCounter);
	void on_frame() override;
};

