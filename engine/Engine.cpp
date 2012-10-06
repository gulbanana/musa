#include <typeinfo>
#include <ctime>
#include <algorithm>
#include <SDL.h>
#include "misc.h"
#include "systems.h"
#include "systems/render/GLImmediateRenderer.h"
#include "Engine.h"
#include "GameState.h"
using namespace std;

#pragma region pimpl
class EngineImpl
{
	static const unsigned maxFPS = 60;
	static const unsigned minFPS = 15;

	vector<unique_ptr<ISystem>> systems;

	shared_ptr<GameState> _state;
	shared_ptr<IRenderer> _renderer;
	
public:
	EngineImpl(unique_ptr<ISystem>&& logic, const string title, int initialWidth, int initialHeight);
	void load_scene(EntityGraph* level);
	void play();
	void frame();
	void add_system(unique_ptr<ISystem>&& system);
};

Engine::Engine(unique_ptr<ISystem>&& logic, const string title, int initialWidth, int initialHeight) : _pimpl(new EngineImpl(move(logic), title, initialWidth, initialHeight)) {}
Engine::~Engine() { delete _pimpl; }
void Engine::load_scene(EntityGraph* level) { _pimpl->load_scene(level); }
void Engine::play() { _pimpl->play(); }
#pragma endregion

EngineImpl::EngineImpl(unique_ptr<ISystem>&& logic, const string title, int initialWidth, int initialHeight)
	: _state(make_shared<GameState>())
{
	
#ifdef _DEBUG
	Uint32 flags = SDL_INIT_EVERYTHING | SDL_INIT_NOPARACHUTE;
#else
	Uint32 flags = SDL_INIT_EVERYTHING;
#endif

    int rc = SDL_Init(flags);
    if (rc != 0)
    {
        SDL_Error(SDL_LASTERROR);
        throw runtime_error("SDL_Init failed");
    }
    
	SDL_WM_SetCaption(title.c_str(), nullptr);	

	_renderer = make_unique<GLImmediateRenderer>(true, true);
	_renderer->resize(initialWidth, initialHeight);

	add_system(make_unique<ControlSystem>(_state));
	add_system(make_unique<MotionSystem>(_state));
	add_system(make_unique<CollisionSystem>());
	add_system(make_unique<RenderSystem>(_renderer));
	add_system(move(logic));
	add_system(make_unique<UISystem>(_state));
}

void EngineImpl::add_system(unique_ptr<ISystem>&& system)
{
	systems.push_back(move(system));
	//sort(begin(systems), end(systems));
}

void EngineImpl::load_scene(EntityGraph* level)
{
	for (auto& entity : level->entity_list())
	{
		for (auto& system : systems)
		{
			auto const& comps = system->required_components();
			if (comps.size() == 0) continue;

			auto matches = count_if(comps.begin(), comps.end(), [&](IComponent::ID requirement)
			{
				return entity->has_component(requirement);
			});

			if (matches == comps.size())
				system->add_entity(entity);
		}
	}
}

void EngineImpl::play()
{
	milliseconds now, mspf, clamp;
	mspf = 1000 / maxFPS;
	clamp = 1000 / minFPS;

	_state->last_frame = SDL_GetTicks();
	
	while (!_state->shouldQuit)
	{
		frame();
        
        now = SDL_GetTicks();
        _state->last_frame_time = min(now - _state->last_frame, clamp);
        _state->last_frame = now;
        
        if (_state->last_frame_time < mspf)
            SDL_Delay(mspf - _state->last_frame_time);
	}

	SDL_Quit();
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