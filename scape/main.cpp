#include "stdafx.h"
#include <core/misc.h>
#include <core/Game.h>
#include <tile/TileEngine.h>
using namespace std;

extern "C"
int _main(int argc, char *argv[])
{
	auto engine = make_unique<TileEngine>();

	Game game(GameSettings("scape techdemo", 1600, 900), move(engine));	
	game.play();

	return 0;
}