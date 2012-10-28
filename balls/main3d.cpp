#include <engine/core.h>
#include <engine/Engine.h>
#include "World.h"
#include "Bouncer.h"
#include "FPSController.h"
using namespace std;

#define WIDTH 1000
#define HEIGHT 1000
#define DEPTH 1000

extern "C"
int main(int argc, char *argv[])
{
    char env[28];
    strcpy(env, "SDL_VIDEO_WINDOW_POS=center");
	SDL_putenv(env);

	vector<unique_ptr<ISystem>> customs;
	customs.push_back(make_unique<Bouncer>(WIDTH, HEIGHT, DEPTH));
	customs.push_back(make_unique<FPSController>());

	Settings settings("balls 3d!", 1200, 675, GraphicsMode::THREE_D);

	Engine game(settings, move(customs));
	
	World scene(true);
	game.load_scene(scene.entities);
	game.play();

	return 0;
}