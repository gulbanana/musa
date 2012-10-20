#include <engine/core.h>
#include <engine/Engine.h>
#include <balls/ResizingBouncer.h>
#include "World.h"
using namespace std;

#define WIDTH 1200
#define HEIGHT 800
#define DEPTH HEIGHT

extern "C"
int main(int argc, char *argv[])
{
	SDL_putenv("SDL_VIDEO_WINDOW_POS=center");

	World scene(false);

	vector<unique_ptr<ISystem>> customs;
	customs.push_back(make_unique<ResizingBouncer>(scene.cameraEntity, WIDTH, HEIGHT, DEPTH));

	Settings settings("balls 3d!", WIDTH, 800, GraphicsMode::TWO_D);

	Engine game(settings, move(customs));
	
	
	game.load_scene(scene.entities);
	game.play();

	return 0;
}