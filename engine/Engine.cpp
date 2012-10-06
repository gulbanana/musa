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

	shared_ptr<GameState> _state;
	shared_ptr<IRenderer> _renderer;
	Scene* _level;
	
public:
	EngineImpl(const string title, int initialWidth, int initialHeight);
	void load_scene(Scene* level, std::unique_ptr<ISystem>&& logic);
	void play();
};

Engine::Engine(const string title, int initialWidth, int initialHeight) : _pimpl(new EngineImpl(title, initialWidth, initialHeight)) {}
void Engine::load_scene(Scene* level, std::unique_ptr<ISystem>&& logic) { _pimpl->load_scene(level, move(logic)); }
void Engine::play() { _pimpl->play(); }
#pragma endregion

EngineImpl::EngineImpl(const string title, int initialWidth, int initialHeight)
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
}

void EngineImpl::load_scene(Scene* level, std::unique_ptr<ISystem>&& logic)
{
	_level = level;

	_level->add_system(make_unique<ControlSystem>(_state));
	_level->add_system(make_unique<MotionSystem>(_state));
	_level->add_system(make_unique<CollisionSystem>());
	_level->add_system(make_unique<RenderSystem>(_renderer));
	_level->add_system(move(logic));
	_level->add_system(make_unique<UISystem>(_state));
}

void EngineImpl::play()
{
	milliseconds now, mspf, clamp;
	mspf = 1000 / maxFPS;
	clamp = 1000 / minFPS;

	_state->last_frame = SDL_GetTicks();
	
	while (!_state->shouldQuit)
	{
		_level->frame();
        
        now = SDL_GetTicks();
        _state->last_frame_time = min(now - _state->last_frame, clamp);
        _state->last_frame = now;
        
        if (_state->last_frame_time < mspf)
            SDL_Delay(mspf - _state->last_frame_time);
	}

	SDL_Quit();
}