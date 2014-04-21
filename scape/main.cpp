#include <scape/stdafx.h>
#include <core/misc.h>
#include <core/Game.h>
#include <core/CustomEngine.h>
#include <tile/archetypes.h>
#include <tile/TileEngine.h>
#include "systems.h"
#include "archetypes.h"
using namespace std;

extern "C"
int _main(int argc, char *argv[])
{
    auto factory = AutonomousEntityFactory();
    auto scene = vector<shared_ptr<IEntity>>();

    auto engine = make_unique<CustomEngine>(make_unique<TileEngine>());
    engine->add_system([]{ return new KBMControlSystem(); });
    engine->add_system([]{ return new PadControlSystem(); });
    
    scene.push_back(factory.create(new Protagonist()));

    Game game(GameSettings("scape techdemo", 1280, 720), move(engine));
    game.load_scene(scene);
	game.play();

	return 0;
}