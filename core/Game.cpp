#include <core/stdafx.h>
#include "systems.h"
#include "misc.h"
#include "Game.h"

using namespace std;

#pragma region pimpl
class GameImpl
{
	static const unsigned maxFPS = 60;
	static const unsigned minFPS = 15;

	vector<unique_ptr<ISystem>> _systems;
	shared_ptr<GameState> _state;
	unique_ptr<IGameEngine> _engine;
	
public:
	GameImpl(GameSettings settings, unique_ptr<IGameEngine> engine);
	void load_scene(vector<shared_ptr<IEntity>> levelEntities);
	void play();
	void frame();
	void add_system(unique_ptr<ISystem> system);
};

Game::Game(GameSettings settings, unique_ptr<IGameEngine> engine) : _pimpl(new GameImpl(settings, move(engine))) {}
Game::~Game() { delete _pimpl; }
void Game::load_scene(vector<shared_ptr<IEntity>> level) { _pimpl->load_scene(level); }
void Game::play() { _pimpl->play(); }
#pragma endregion

GameImpl::GameImpl(GameSettings settings, unique_ptr<IGameEngine> engine) : _state(make_shared<GameState>()), _systems(), _engine(move(engine))
{
    platform->set_window_title(settings.window_title);

	add_system(make_unique<ControlSystem>(_state));

	for (auto& system : _engine->get_systems(settings, _state))
		add_system(move(system));
}

void GameImpl::add_system(unique_ptr<ISystem> system)
{
	_systems.push_back(move(system));
	//sort(begin(systems), end(systems));
}

void GameImpl::load_scene(vector<shared_ptr<IEntity>> entities)
{
	for (auto& entity : entities)
		for (auto& system : _systems)
			system->on_entity(entity);
}

void GameImpl::play()
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

void GameImpl::frame()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
		for(auto& system : _systems)
			if (system->on_event(event)) 
				break;

	for(auto& system : _systems)
		system->on_frame();
}