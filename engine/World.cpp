#include "misc.h"
#include "World.h"
#include "InputSystem.h"
#include "ShapeRenderSystem.h"
#include "UIRenderSystem.h"
#include "MotionSystem.h"
#include "CollisionSystem.h"
#include "PhysicsSystem.h"
#include <typeinfo>
#include <ctime>
#include <SFML/Graphics.hpp>
using namespace std;

class WorldImpl
{
	vector<unique_ptr<ISystem>> systems;
	vector<shared_ptr<IEntity>> entities;
	unique_ptr<sf::RenderWindow> mainWindow;
	int fps;

	void frame();

public:
	WorldImpl(string title);
	void add_entity(shared_ptr<IEntity> entity);
	void add_system(unique_ptr<ISystem> system);
	void play();
};


World::World(string title) : _pimpl(new WorldImpl(title)) {}
WorldImpl::WorldImpl(string title)
{
	fps = 0;

	mainWindow = make_unique<sf::RenderWindow>(sf::VideoMode(700, 700), title);
	mainWindow->setVerticalSyncEnabled(true);

	sf::Font font;
	font.loadFromFile("C:\\Windows\\Fonts\\Arial.ttf");

	add_system(make_unique<InputSystem>(mainWindow.get()));
	add_system(make_unique<MotionSystem>(700.f, 700.f));
	add_system(make_unique<CollisionSystem>());
	add_system(make_unique<PhysicsSystem>());
	add_system(make_unique<ShapeRenderSystem>(font, mainWindow.get()));
	add_system(make_unique<UIRenderSystem>(font, mainWindow.get(), fps));
}

void World::play() { _pimpl->play(); }
void WorldImpl::play()
{
	sf::Clock clock;
	while (mainWindow->isOpen())
	{
		clock.restart();
		frame();
		fps = (int)(1.f / clock.getElapsedTime().asSeconds());
	}
}

void World::add_entity(shared_ptr<IEntity> entity) { _pimpl->add_entity(entity); }
void WorldImpl::add_entity(shared_ptr<IEntity> entity)
{
	entities.push_back(entity);

	for (auto& system : systems)
	{
		auto comps = system->required_components();
		if (comps.size() == 0) return;

		int matches = count_if(comps.begin(), comps.end(), [&](CID requirement)
		{
			return entity->has_component(requirement);
		});

		if (matches == comps.size())
			system->add_entity(entity);
	}
}

void World::add_system(unique_ptr<ISystem> system) { _pimpl->add_system(std::move(system)); }
void WorldImpl::add_system(unique_ptr<ISystem> system)
{
	systems.push_back(std::move(system));
}

void WorldImpl::frame()
{
	for(auto& system : systems)
	{
		system->frame();
	}

	mainWindow->display();
}