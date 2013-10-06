#include <tile/stdafx.h>
#include <core/misc.h>
#include "TileEngine.h"
#include "systems.h"
using namespace std;

vector<unique_ptr<ISystem>> TileEngine::create_systems()
{
    vector<unique_ptr<ISystem>> tileCore;

	auto blit = make_unique<GLBlitSystem>(_surface);
	auto render = make_unique<RenderSystem>(_state, blit.get());
    auto ui = make_unique<UISystem>(_state, blit.get());
    auto keyboard = make_unique<KBMControlSystem>();
    auto gamepad = make_unique<PadControlSystem>();
    auto motion = make_unique<MotionSystem>(_state);

    tileCore.push_back(move(keyboard));
    tileCore.push_back(move(gamepad));

    tileCore.push_back(move(motion));

	tileCore.push_back(move(render));
    tileCore.push_back(move(ui));

	tileCore.push_back(move(blit));

	return tileCore;
}