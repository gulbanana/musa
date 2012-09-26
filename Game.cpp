#include "misc.h"
#include "Game.h"
#include "InputSystem.h"
#include "RenderSystem.h"
#include "MotionSystem.h"
#include "CollisionSystem.h"
#include "Ball.h"
#include "Obstacle.h"
#include "Backdrop.h"
#include <functional>
#include <typeinfo>
#include <random>
using namespace std;

Game::Game()
{
	mainWindow = make_unique<sf::RenderWindow>(sf::VideoMode(700, 700), "Musa Musaceae - engine test");

	add_system(make_unique<InputSystem>(mainWindow.get()));
	add_system(make_unique<CollisionSystem>(700.f, 700.f));
	add_system(make_unique<MotionSystem>());
	add_system(make_unique<RenderSystem>(mainWindow.get()));

	add_entity(make_shared<Obstacle>(sf::Color::White, 200.f, 300.f));
	add_entity(make_shared<Backdrop>(sf::Color::White, 400.f, 300.f));

	add_entity(make_shared<Ball>(sf::Color::Cyan, 100.f, 100.f));
	add_entity(make_shared<Ball>(sf::Color::Magenta, 200.f, 400.f));
	add_entity(make_shared<Ball>(sf::Color::Yellow, 300.f, 200.f));
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
		if (comps.size() == 0) return;

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