#include <core/stdafx.h>
#include "systems.h"
#include "misc.h"
#include "Game.h"

using namespace std;

#pragma region pimpl
class GameImpl
{
private:
	static const unsigned maxFPS = 60;
	static const unsigned minFPS = 15;

    //the Game owns all these objects and will take care of destroying them in the correct order
    //resources like the state and entities are provided to them as non-owning references
	unique_ptr<GameState> _state;
	unique_ptr<IGameEngine> _engine;
	vector<unique_ptr<ISystem>> _systems;

    void frame();

public:
	GameImpl(GameSettings settings, unique_ptr<IGameEngine> engine);
	void load_scene(vector<shared_ptr<IEntity>> levelEntities);
	void play();
};

Game::Game(GameSettings settings, unique_ptr<IGameEngine> engine) : _pimpl(new GameImpl(settings, move(engine))) {}
Game::~Game() { delete _pimpl; }
void Game::load_scene(vector<shared_ptr<IEntity>> level) { _pimpl->load_scene(level); }
void Game::play() { _pimpl->play(); }
#pragma endregion

GameImpl::GameImpl(GameSettings settings, unique_ptr<IGameEngine> engine) : 
    _state(make_unique<GameState>()), _engine(move(engine)), _systems()
{
    _engine->init(make_unique<GameSettings>(settings), _state.get());

	_systems.push_back(make_unique<ControlSystem>(_state.get()));
	for (auto& system : _engine->create_systems())
		_systems.push_back(move(system));

    //todo: create system dependency graph
}

void GameImpl::load_scene(vector<shared_ptr<IEntity>> entities)
{
    //todo: have these things owned by a manager or something
    //for now they are shared_ptrs

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