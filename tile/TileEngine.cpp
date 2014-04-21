#include <tile/stdafx.h>
#include <core/misc.h>
#include <core/systems.h>
#include "TileEngine.h"
#include "systems.h"
using namespace std;

void TileEngine::init(std::unique_ptr<GameSettings> settings, GameState* state)
{
    GLEngineBase::init(move(settings), state);

    auto blit = make_unique<GLBlitSystem>(_surface);

    _ownedSystems.emplace(new ControlSystem(_state));
    _ownedSystems.emplace(new RenderSystem(_state, blit.get()));
    _ownedSystems.emplace(new UISystem(_state, blit.get()));
    _ownedSystems.emplace(new MotionSystem(_state));
    _ownedSystems.insert(move(blit));
}

set<ISystem*> TileEngine::create_systems()
{
    set<ISystem*> tileCore;

    for (auto& system : _ownedSystems)
        tileCore.insert(system.get());

	return tileCore;
}