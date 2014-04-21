#include <mesh/stdafx.h>
#include <core/misc.h>
#include <core/systems.h>
#include "systems.h"
#include "systems/render/GLImmediateRenderer.h"
#include "MeshEngine.h"
using namespace std;

MeshEngine::MeshEngine(bool wireframe) : _wireframe(wireframe) {}

void MeshEngine::init(unique_ptr<GameSettings> settings, GameState* state)
{
    GLEngineBase::init(move(settings), state);

    shared_ptr<IRenderer> renderer = make_unique<GLImmediateRenderer>(_surface, _wireframe);	//wireframe mode
    renderer->set_viewport(_settings->initial_width, _settings->initial_height);

    _ownedSystems.emplace(new ControlSystem(_state));
    _ownedSystems.emplace(new MotionSystem(_state));
    _ownedSystems.emplace(new CollisionSystem());
    _ownedSystems.emplace(new RenderSystem(renderer));
    _ownedSystems.emplace(new UISystem(_state));
}

set<ISystem*> MeshEngine::create_systems()
{
    set<ISystem*> meshCore;

    for (auto& system : _ownedSystems)
        meshCore.insert(system.get());

    return meshCore;
}