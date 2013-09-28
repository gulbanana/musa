#include "stdafx.h"
#include <core/Game.h>
#include <core/misc.h>
#include <core/CustomEngine.h>
#include <mesh/systems.h>
#include <mesh/MeshEngine.h>
#include "World.h"
#include "Bouncer.h"
using namespace std;

#define WIDTH 1000
#define HEIGHT 1000
#define DEPTH 1000

extern "C"
int _main(int argc, char *argv[])
{
	vector<unique_ptr<ISystem>> customs;
	customs.push_back(make_unique<Bouncer>(WIDTH, HEIGHT, DEPTH));
	customs.push_back(make_unique<FPSController>());

	auto settings = GameSettings("balls 3d!", 1200, 675);
	auto engine = make_unique<CustomEngine>(make_unique<MeshEngine>(true));
	engine->add_system(make_unique<Bouncer>(WIDTH, HEIGHT, DEPTH));
	engine->add_system(make_unique<FPSController>());

	Game game(settings, move(engine));
	
	World scene(true);
	game.load_scene(scene.entities);
	game.play();

	return 0;
}