#include <mesh/stdafx.h>
#include <core/misc.h>
#include "systems.h"
#include "systems/render/GLImmediateRenderer.h"
#include "MeshEngine.h"
using namespace std;

MeshEngine::MeshEngine(bool wireframe) : _wireframe(wireframe) {}

vector<unique_ptr<ISystem>> MeshEngine::create_systems()
{
    vector<unique_ptr<ISystem>> meshEngineCore;

	shared_ptr<IRenderer> renderer = make_unique<GLImmediateRenderer>(_surface, _wireframe);	//wireframe mode
	renderer->set_viewport(_settings->initial_width, _settings->initial_height);
	
	meshEngineCore.push_back(make_unique<MotionSystem>(_state));
	meshEngineCore.push_back(make_unique<CollisionSystem>());
	meshEngineCore.push_back(make_unique<RenderSystem>(renderer));
	meshEngineCore.push_back(make_unique<UISystem>(_state));

	return meshEngineCore;
}