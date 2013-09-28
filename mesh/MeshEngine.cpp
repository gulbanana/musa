#include <mesh/stdafx.h>
#include <core/misc.h>
#include "systems.h"
#include "systems/render/GLImmediateRenderer.h"
#include "MeshEngine.h"
using namespace std;

MeshEngine::MeshEngine(bool wireframe) : _wireframe(wireframe)
{
}

MeshEngine::~MeshEngine()
{
}

vector<unique_ptr<ISystem>> MeshEngine::get_systems(GameSettings settings, shared_ptr<GameState> state)
{
	shared_ptr<IRenderer> renderer = make_unique<GLImmediateRenderer>(_wireframe);	//wireframe mode
	renderer->set_viewport(settings.initial_width, settings.initial_height);

	vector<unique_ptr<ISystem>> meshEngineCore;
	meshEngineCore.push_back(make_unique<MotionSystem>(state));
	meshEngineCore.push_back(make_unique<CollisionSystem>());
	meshEngineCore.push_back(make_unique<RenderSystem>(renderer));

	return meshEngineCore;
}