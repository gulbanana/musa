#include <engine/core.h>
#include <engine/Engine.h>
#include "World.h"
using namespace std;

#define WIDTH 1600
#define HEIGHT 900

extern "C"
int _main(int argc, char *argv[])
{
	World scene(false);

	vector<unique_ptr<ISystem>> customs;
	Settings config("scape", WIDTH, HEIGHT, GraphicsMode::TWO_D);
	Engine game(config, move(customs));
	
	game.load_scene(scene.entities);
	game.play();

	return 0;
}