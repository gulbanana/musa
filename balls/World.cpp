#include <engine/core.h>
#include <engine/archetypes.h>
#include <engine/components.h>
#include <engine/ResourceManager.h>
#include <random>
#include "World.h"
#include "FPSCamera.h"
#include "Obstacle.h"
#include "Ball.h"
using namespace std;

#define WIDTH 1000
#define HEIGHT 1000
#define DEPTH 1000

World::World(bool is3d)
{
	//useful rngs
	default_random_engine generator;
	uniform_real_distribution<glm::float_t> zero2one(0.0, 1.0);
	uniform_real_distribution<glm::float_t> half2half(-0.5, 0.5);
	uniform_real_distribution<glm::float_t> threesixty(0.0, 360.0);

	//musacea factories
	ResourceManager loader;
	auto factory = make_unique<AutonomousEntityFactory>();

	//camera
	if (is3d)
	{
		auto camera = new FPSCamera(point(WIDTH/2, HEIGHT/2, DEPTH));
		entities.emplace_back(factory->create(camera));
		cameraEntity = entities.back();
		_archetypes.emplace_back(camera);
	}
	else
	{
		auto camera = new Camera2D(WIDTH, HEIGHT, HEIGHT);
		entities.emplace_back(factory->create(camera));
		cameraEntity = entities.back();
		_archetypes.emplace_back(camera);
	}

	//brushes
	auto brush = [&](colour c){ return (SolidColourBrush*)loader.load_brush(c); };

	//immobiles
	box6 smallBox((coord)-50, (coord)-150, (coord)-30, (coord)50, (coord)150, (coord)30);
	box6 bigBox((coord)-500, (coord)-500, (coord)-500, (coord)500, (coord)500, (coord)500);
	auto blueBox = loader.load_primitive(brush(Colour::BLUE), Primitive::Prism, &smallBox);
	auto redBox = loader.load_primitive(brush(Colour::RED), Primitive::Prism, &smallBox);
	Obstacle solidWall(redBox, true);
	Obstacle decorativeWall(blueBox, false);

	entities.emplace_back(factory->create(&solidWall));
	entities.back()->add_component<CPosition>(make_unique<CPosition>(point(200, 500, WIDTH/2)));

	entities.emplace_back(factory->create(&decorativeWall));
	entities.back()->add_component<CPosition>(make_unique<CPosition>(point(400, 500, WIDTH/2)));
	entities.back()->add_component<CVelocity>(make_unique<CVelocity>(point(), angles(0, 45, 0)));

	entities.emplace_back(factory->create(&solidWall));
	entities.back()->add_component<CPosition>(make_unique<CPosition>(point(600, 500, WIDTH/2)));

	entities.emplace_back(factory->create(&decorativeWall));
	entities.back()->add_component<CPosition>(make_unique<CPosition>(point(800, 500, WIDTH/2)));
	entities.back()->add_component<CVelocity>(make_unique<CVelocity>(point(), angles(45, 0, 0)));

	//fixed balls
	coord smallBall = 15;
	coord bigBall = 35;
	Ball cyanBall(loader.load_primitive(brush(Colour::CYAN), Primitive::Sphere, &bigBall));
	Ball magentaBall(loader.load_primitive(brush(Colour::MAGENTA), Primitive::Sphere, &bigBall));
	Ball yellowBall(loader.load_primitive(brush(Colour::YELLOW), Primitive::Sphere, &bigBall));
	
	entities.emplace_back(factory->create(&cyanBall));
	entities.back()->add_component<CPosition>(make_unique<CPosition>(point(800, 800, 0)));
	entities.back()->add_component<CVelocity>(make_unique<CVelocity>(point(100, -100, 0)));

	entities.emplace_back(factory->create(&magentaBall));
	entities.back()->add_component<CPosition>(make_unique<CPosition>(point(200, 500, 0)));
	entities.back()->add_component<CVelocity>(make_unique<CVelocity>(point(100, 100, 0)));

	entities.emplace_back(factory->create(&yellowBall));
	entities.back()->add_component<CPosition>(make_unique<CPosition>(point(800, 200, 0)));
	entities.back()->add_component<CVelocity>(make_unique<CVelocity>(point(-100, 100, 0)));
	
	//random balls
	auto small = (coord)15;
	Ball greenBall(loader.load_primitive(brush(colour(0.f, 1.f, 0.f, 0.75f)), Primitive::Sphere, &smallBall));

	for (int i = 0; i < 35; i++) {
		entities.emplace_back(factory->create(&greenBall));
		if (is3d)
		{
		entities.back()->add_component<CPosition>(make_unique<CPosition>(point(zero2one(generator) * WIDTH, zero2one(generator) * HEIGHT, zero2one(generator) * DEPTH)));
		entities.back()->add_component<CVelocity>(make_unique<CVelocity>(point(half2half(generator) * 500, half2half(generator) * 500, half2half(generator) * 500)));
		}
		else
		{
		entities.back()->add_component<CPosition>(make_unique<CPosition>(point(zero2one(generator) * WIDTH, zero2one(generator) * HEIGHT, 0)));
		entities.back()->add_component<CVelocity>(make_unique<CVelocity>(point(half2half(generator) * 500, half2half(generator) * 500, 0)));
		}
	}

	//skybox
	if (is3d)
	{
		auto whiteBox = loader.load_primitive(brush(Colour::WHITE), Primitive::Prism, &bigBox);
		Obstacle skybox(whiteBox, false);
		entities.emplace_back(factory->create(&skybox));
		entities.back()->add_component<CPosition>(make_unique<CPosition>(point(500, 500, 500)));
	}
}