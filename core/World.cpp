#include "misc.h"
#include "World.h"
#include "InputSystem.h"
#include "RenderSystem.h"
#include "MotionSystem.h"
#include "CollisionSystem.h"
#include "Ball.h"
#include "Obstacle.h"
#include "Backdrop.h"
#include <typeinfo>
#include <ctime>
#include <SFML/Graphics.hpp>
using namespace std;

class WorldImpl
{
	std::unique_ptr<sf::RenderWindow> mainWindow;
	std::vector<std::unique_ptr<ISystem>> systems;
	std::vector<std::shared_ptr<IEntity>> entities;

public:
	WorldImpl();

	void add_entity(std::shared_ptr<IEntity> entity);
	void add_system(std::unique_ptr<ISystem> system);
	void play();
};


World::World() : _pimpl(new WorldImpl()) {}
WorldImpl::WorldImpl()
{
	mainWindow = make_unique<sf::RenderWindow>(sf::VideoMode(700, 700), "Musa Musaceae - engine test");
	mainWindow->setVerticalSyncEnabled(true);
	mainWindow->setFramerateLimit(60);

	add_system(make_unique<InputSystem>(mainWindow.get()));
	add_system(make_unique<CollisionSystem>(700.f, 700.f));
	add_system(make_unique<MotionSystem>());
	add_system(make_unique<RenderSystem>(mainWindow.get()));
}

void World::play() { _pimpl->play(); }
void WorldImpl::play()
{
	while (mainWindow->isOpen())
	{
		for_each(begin(systems), end(systems), [](unique_ptr<ISystem>& system)
		{
			system->frame();
		});

		mainWindow->display();
	}
}

void World::add_entity(shared_ptr<IEntity> entity) { _pimpl->add_entity(entity); }
void WorldImpl::add_entity(shared_ptr<IEntity> entity)
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

void World::add_system(unique_ptr<ISystem> system) { _pimpl->add_system(std::move(system)); }
void WorldImpl::add_system(unique_ptr<ISystem> system)
{
	systems.push_back(std::move(system));
}