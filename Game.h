#pragma once
#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>
#include "ISystem.h"

class Game
{
	std::unique_ptr<sf::RenderWindow> mainWindow;
	std::vector<std::unique_ptr<ISystem>> systems;
	std::vector<std::shared_ptr<IEntity>> entities;

private:
	void frame();
	void add_entity(std::shared_ptr<IEntity> entity);
	void add_system(std::unique_ptr<ISystem> system);

public:
	Game();
	void play();
};

