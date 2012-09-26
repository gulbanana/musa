#pragma once
#include <SFML/Graphics.hpp>
#include "ISystem.h"

class RenderSystem : public ISystem
{
	sf::Font font;
	sf::RenderTarget* surface;

public:
	RenderSystem(sf::RenderTarget* s);

	std::vector<std::string> required_components() override;
	void on_frame() override;
	void on_entity(std::shared_ptr<IEntity> entity) override;
	
};

