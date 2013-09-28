#include "stdafx.h"
#include <core/misc.h>
#include <mesh/archetypes.h>
#include <mesh/components.h>
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
	auto brush = [&](colour c){ return (SolidColourBrush*)_loader.load_brush(c); };

	//immobiles
	box6 smallBox((coord)-50, (coord)-150, (coord)-30, (coord)50, (coord)150, (coord)30);
	box6 bigBox((coord)-500, (coord)-500, (coord)-500, (coord)500, (coord)500, (coord)500);
	auto blueBox = _loader.load_primitive(brush(Colour::BLUE), Primitive::Prism, &smallBox);
	auto redBox = _loader.load_primitive(brush(Colour::RED), Primitive::Prism, &smallBox);
	auto solidWall = new Obstacle(redBox, true);
	auto decorativeWall = new Obstacle(blueBox, false);
	_archetypes.emplace_back(solidWall);
	_archetypes.emplace_back(decorativeWall);

	entities.emplace_back(factory->create(solidWall));
	entities.back()->add_component<CTransform>(make_unique<CTransform>(point(200, 500, WIDTH/2)));

	entities.emplace_back(factory->create(decorativeWall));
	entities.back()->add_component<CTransform>(make_unique<CTransform>(point(400, 500, WIDTH/2)));
	entities.back()->add_component<CVelocity>(make_unique<CVelocity>(point(), eulers(0, glm::radians(45.0), 0)));

	entities.emplace_back(factory->create(solidWall));
	entities.back()->add_component<CTransform>(make_unique<CTransform>(point(600, 500, WIDTH/2)));

	entities.emplace_back(factory->create(decorativeWall));
	entities.back()->add_component<CTransform>(make_unique<CTransform>(point(800, 500, WIDTH/2)));
	entities.back()->add_component<CVelocity>(make_unique<CVelocity>(point(), eulers(glm::radians(45.0), 0, 0)));

	//fixed balls
	coord bigBall = 35;
	auto cyanBall = new Ball(_loader.load_primitive(brush(Colour::CYAN), Primitive::Sphere, &bigBall));
	auto magentaBall = new Ball(_loader.load_primitive(brush(Colour::MAGENTA), Primitive::Sphere, &bigBall));
	auto yellowBall = new Ball(_loader.load_primitive(brush(Colour::YELLOW), Primitive::Sphere, &bigBall));
	_archetypes.emplace_back(cyanBall);
	_archetypes.emplace_back(magentaBall);
	_archetypes.emplace_back(yellowBall);
	
	entities.emplace_back(factory->create(cyanBall));
	entities.back()->add_component<CTransform>(make_unique<CTransform>(point(800, 800, 300)));
	entities.back()->add_component<CVelocity>(make_unique<CVelocity>(point(100, -100, 0)));

	entities.emplace_back(factory->create(magentaBall));
	entities.back()->add_component<CTransform>(make_unique<CTransform>(point(200, 500, 500)));
	entities.back()->add_component<CVelocity>(make_unique<CVelocity>(point(100, 100, 0)));

	entities.emplace_back(factory->create(yellowBall));
	entities.back()->add_component<CTransform>(make_unique<CTransform>(point(800, 200, 700)));
	entities.back()->add_component<CVelocity>(make_unique<CVelocity>(point(-100, 100, 0)));
	
	//random balls
	coord smallBall = 15;
	auto greenBall = new Ball(_loader.load_primitive(brush(colour(0.f, 1.f, 0.f, 0.75f)), Primitive::Sphere, &smallBall));
	_archetypes.emplace_back(greenBall);

	for (int i = 0; i < 35; i++) {
		entities.emplace_back(factory->create(greenBall));
		if (is3d)
		{
		entities.back()->add_component<CTransform>(make_unique<CTransform>(point(zero2one(generator) * WIDTH, zero2one(generator) * HEIGHT, zero2one(generator) * DEPTH)));
		entities.back()->add_component<CVelocity>(make_unique<CVelocity>(point(half2half(generator) * 500, half2half(generator) * 500, half2half(generator) * 500)));
		}
		else
		{
		entities.back()->add_component<CTransform>(make_unique<CTransform>(point(zero2one(generator) * WIDTH, zero2one(generator) * HEIGHT, 0)));
		entities.back()->add_component<CVelocity>(make_unique<CVelocity>(point(half2half(generator) * 500, half2half(generator) * 500, 0)));
		}
	}

	//skybox
	if (is3d)
	{
		auto whiteBox = _loader.load_primitive(brush(Colour::WHITE), Primitive::Prism, &bigBox);
		Obstacle skybox(whiteBox, false);
		entities.emplace_back(factory->create(&skybox));
		entities.back()->add_component<CTransform>(make_unique<CTransform>(point(500, 500, 500)));
	}
}
