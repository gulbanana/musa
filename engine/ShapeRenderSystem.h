#pragma once
#include <SFML/Graphics.hpp>
#include "ISystem.h"

class ShapeRenderSystem : public ISystem
{
	sf::Font font;
	sf::RenderTarget* surface;

	sf::CircleShape reusableCircle;
	sf::RectangleShape reusableRectangle;
	sf::Text reusableTextRun;

public:
	ShapeRenderSystem(sf::Font labelFont, sf::RenderTarget* s);

	std::vector<IComponent::ID> required_components() override;
	void on_frame() override;
	void on_entity(std::shared_ptr<IEntity> entity) override;
	
};

