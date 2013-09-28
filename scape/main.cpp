#include "stdafx.h"
#include <core/misc.h>
#include <core/Engine.h>
using namespace std;

extern "C"
int _main(int argc, char *argv[])
{
	vector<unique_ptr<ISystem>> customs;

	Engine game(Settings("scape techdemo", 1600, 900, GraphicsMode::TILE), move(customs));	
	game.play();

	return 0;
}