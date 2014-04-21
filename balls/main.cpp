#include "stdafx.h"
#include <core/misc.h>
#include <core/Game.h>
#include <core/CustomEngine.h>
#include <mesh/MeshEngine.h>
#include "ResizingBouncer.h"
#include "World.h"
using namespace std;

#define WIDTH 1200
#define HEIGHT 800
#define DEPTH HEIGHT

extern "C"
int _main(int argc, char *argv[])
{
	World scene(false);

	auto settings = GameSettings("balls!", WIDTH, 800);
	auto engine = make_unique<CustomEngine>(make_unique<MeshEngine>(false));
    engine->add_system([&](GameState*){ return new ResizingBouncer(scene.cameraEntity, WIDTH, HEIGHT, DEPTH); });

	Game game(settings, move(engine));
	
	game.load_scene(scene.entities);
	game.play();

	return 0;
}