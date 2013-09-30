#include "stdafx.h"
#include <core/misc.h>
#include <core/Game.h>
#include <tile/archetypes.h>
#include <tile/TileEngine.h>
using namespace std;

extern "C"
int _main(int argc, char *argv[])
{
	auto engine = make_unique<TileEngine>();

	Game game(GameSettings("scape techdemo", 1280, 720), move(engine));

    auto factory = AutonomousEntityFactory();
    auto scene = vector<shared_ptr<IEntity>>();
    
    scene.push_back(factory.create(new Protagonist()));

    game.load_scene(scene);
	game.play();

	return 0;
}