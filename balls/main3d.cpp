#include "stdafx.h"
#include <core/Engine.h>
#include <core/misc.h>
#include <mesh/systems.h>
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

	Settings settings("balls 3d!", 1200, 675, GraphicsMode::MESH_3D);

	Engine game(settings, move(customs));
	
	World scene(true);
	game.load_scene(scene.entities);
	game.play();

	return 0;
}