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
	vector<ISystem*> _orderedSystems;

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
    _state(make_unique<GameState>()), _engine(move(engine)), _orderedSystems()
{
    _engine->init(make_unique<GameSettings>(settings), _state.get());

    auto unorderedSystems = _engine->create_systems();

    //linearise the set of systems based on the expressed dependencies of each system
    while (unorderedSystems.size() > 0)
    {
        auto currentSize = unorderedSystems.size();

        for (auto system = begin(unorderedSystems); system != end(unorderedSystems);)
        {
            auto canMove = true;
            auto requirements = (*system)->required_systems();
            for (auto requirement = begin(requirements); canMove && requirement != end(requirements); requirement++)
            {
                if (!any_of(begin(_orderedSystems), end(_orderedSystems), [=](ISystem* s){return s->id() == *requirement; }))
                {
                    canMove = false;
                }
            }

            if (canMove)
            {
                _orderedSystems.push_back(*system);
                system = unorderedSystems.erase(system);
            }
            else
            {
                system++;
            }
        }

        if (currentSize == unorderedSystems.size())
        {
            auto error = string("System init error: unable to satisfy prereqs for ");
            for (auto system : unorderedSystems)
            {
                error = error + to_string(system) + ",";
            }
            throw runtime_error(error);
        }
    }
}

void GameImpl::load_scene(vector<shared_ptr<IEntity>> entities)
{
    //todo: have these things owned by a manager or something
    //for now they are shared_ptrs

	for (auto& entity : entities)
        for (auto& system : _orderedSystems)
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
        for (auto& system : _orderedSystems)
			if (system->on_event(event)) 
				break;

    for (auto& system : _orderedSystems)
		system->on_frame();
}