#include "misc.h"
#include "Game.h"
#include "InputSystem.h"
#include "RenderSystem.h"
#include "MotionSystem.h"
#include "GreenBall.h"
#include <functional>
#include <typeinfo>
using namespace std;

Game::Game()
{
	mainWindow = make_unique<sf::RenderWindow>(sf::VideoMode(800, 600), "Musa Musaceae - engine test");

	add_system(make_unique<InputSystem>(mainWindow.get()));
	add_system(make_unique<MotionSystem>());
	add_system(make_unique<RenderSystem>(mainWindow.get()));

	add_entity(make_shared<GreenBall>());
}

void Game::play()
{
	while (mainWindow->isOpen())
	{
		frame();
	}
}

void Game::frame()
{
	for_each(begin(systems), end(systems), [](unique_ptr<ISystem>& system)
	{
		system->frame();
	});

	mainWindow->display();
}

void Game::add_entity(shared_ptr<IEntity> entity)
{
	entities.push_back(entity);

	for_each(systems.begin(), systems.end(), [&](unique_ptr<ISystem>& system)
	{
		auto comps = system->required_components();

		int matches = count_if(comps.begin(), comps.end(), [&](string requirementName)
		{
			return entity->has_component(requirementName);
		});

		if (matches == comps.size())
			system->add_entity(entity);
	});
}

void Game::add_system(unique_ptr<ISystem> system)
{
	systems.push_back(std::move(system));
}