#include <core/stdafx.h>
#include <mesh/systems.h>
#include <mesh/systems/render/GLImmediateRenderer.h>
#include "systems.h"
#include "misc.h"
#include "GameState.h"
#include "Engine.h"

using namespace std;

#pragma region pimpl
class EngineImpl
{
	static const unsigned maxFPS = 60;
	static const unsigned minFPS = 15;

	vector<unique_ptr<ISystem>> systems;

	shared_ptr<GameState> _state;
	
public:
	EngineImpl(Settings& settings, vector<unique_ptr<ISystem>> customLogic);
	void load_scene(vector<shared_ptr<IEntity>> levelEntities);
	void play();
	void frame();
	void add_system(unique_ptr<ISystem> system);

private:
	void init_mesh2D(Settings&);
	void init_mesh3D(Settings&);
	void init_tiles(Settings&);
};

Engine::Engine(Settings& settings, vector<unique_ptr<ISystem>> customLogic) : _pimpl(new EngineImpl(settings, move(customLogic))) {}
Engine::~Engine() { delete _pimpl; }
void Engine::load_scene(vector<shared_ptr<IEntity>> level) { _pimpl->load_scene(level); }
void Engine::play() { _pimpl->play(); }
#pragma endregion

EngineImpl::EngineImpl(Settings& settings, vector<unique_ptr<ISystem>> customLogic) : _state(make_shared<GameState>())
{
    platform->set_window_title(settings.window_title);

	add_system(make_unique<ControlSystem>(_state));

	switch (settings.mode)
	{
	case GraphicsMode::MESH_2D:
		init_mesh2D(settings);
		break;

	case GraphicsMode::MESH_3D:
		init_mesh3D(settings);
		break;

	case GraphicsMode::TILE:
		init_tiles(settings);
		break;
	}

	for (auto& customSystem : customLogic)
	{
		add_system(move(customSystem));
	}
	
	add_system(make_unique<UISystem>(_state));
}

void EngineImpl::add_system(unique_ptr<ISystem> system)
{
	systems.push_back(move(system));
	//sort(begin(systems), end(systems));
}

void EngineImpl::load_scene(vector<shared_ptr<IEntity>> entities)
{
	for (auto& entity : entities)
		for (auto& system : systems)
			system->add_entity(entity);
}

void EngineImpl::play()
{
	milliseconds now, mspf, clamp;
	mspf = 1000 / maxFPS;
	clamp = 1000 / minFPS;

	_state->last_frame = platform->get_ticks();
	
	while (!_state->shouldQuit)
	{
		frame();
        
        now = platform->get_ticks();
        _state->last_frame_time = min<milliseconds>(now - _state->last_frame, clamp);
        _state->last_frame = now;
        
		//XXX it would be better to rely on vsync, perhaps
        if (_state->last_frame_time < mspf)
            platform->sleep_ticks(mspf - _state->last_frame_time);
	}
}

void EngineImpl::frame()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
		for(auto& system : systems)
			if (system->on_event(event)) 
				break;

	for(auto& system : systems)
		system->on_frame();
}

void EngineImpl::init_mesh2D(Settings& settings)
{
	shared_ptr<IRenderer> renderer = make_unique<GLImmediateRenderer>(false);
	renderer->set_viewport(settings.initial_width, settings.initial_height);

	add_system(make_unique<MotionSystem>(_state));
	add_system(make_unique<CollisionSystem>());
	add_system(make_unique<RenderSystem>(renderer));
}

void EngineImpl::init_mesh3D(Settings& settings)
{
	shared_ptr<IRenderer> renderer = make_unique<GLImmediateRenderer>(true);	//wireframe mode
	renderer->set_viewport(settings.initial_width, settings.initial_height);

	add_system(make_unique<MotionSystem>(_state));
	add_system(make_unique<CollisionSystem>());
	add_system(make_unique<RenderSystem>(renderer));
}

void EngineImpl::init_tiles(Settings& settings)
{
}
