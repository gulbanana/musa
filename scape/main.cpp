#include "stdafx.h"
#include <core/misc.h>
#include <core/Game.h>
#include <tile/TilesEngine.h>
using namespace std;

extern "C"
int _main(int argc, char *argv[])
{
	auto engine = make_unique<TilesEngine>();

	Game game(GameSettings("scape techdemo", 1600, 900), move(engine));	
	game.play();

	return 0;
}