#include <tile/stdafx.h>
#include <core/misc.h>
#include "TileEngine.h"
#include "systems.h"
using namespace std;

TileEngine::TileEngine() {}

TileEngine::~TileEngine() {}

vector<unique_ptr<ISystem>> TileEngine::get_systems(GameSettings settings, shared_ptr<GameState> state)
{
	vector<unique_ptr<ISystem>> empty;

	auto blit = make_unique<GLBlitSystem>(settings.initial_width, settings.initial_height);
	auto render = make_unique<RenderSystem>(blit.get(), state);
    auto ui = make_unique<UISystem>(blit.get(), state);
    auto keyboard = make_unique<KBMControlSystem>();
    auto gamepad = make_unique<PadControlSystem>();
    auto motion = make_unique<MotionSystem>(state);

    empty.push_back(move(keyboard));
    empty.push_back(move(gamepad));

    empty.push_back(move(motion));

	empty.push_back(move(render));
    empty.push_back(move(ui));

	empty.push_back(move(blit));

	return empty;
}