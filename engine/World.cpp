#include <typeinfo>
#include <ctime>
#include <algorithm>
#include <SDL.h>
#include "misc.h"
#include "systems.h"
#include "systems/render/GLImmediateRenderer.h"
#include "World.h"
#include "GameState.h"
using namespace std;

#pragma region sdlcall
void check(std::function<int()> sdlCall)
{
	int rc = sdlCall();
	if (rc != 0)
		throw std::runtime_error(SDL_GetError());
}

template<typename T>
T check(std::function<T()> sdlCall)
{
	T ret = sdlCall();
	if (ret == nullptr)
		throw std::runtime_error(SDL_GetError());
	return ret;
}
#pragma endregion

#pragma region pimpl
class WorldImpl
{
	static const unsigned maxFPS = 60;

	SDL_Surface* surface;
	SDL_Event event;
	shared_ptr<GameState> state;
	vector<unique_ptr<ISystem>> systems;
	vector<shared_ptr<IEntity>> entities;
	
	void frame();

public:
	WorldImpl(const string title, int width, int height);
	void add_entity(shared_ptr<IEntity> entity);
	void add_system(unique_ptr<ISystem> system);
	void play();
};

World::World(const string title) : _pimpl(new WorldImpl(title, 800, 600)) {}
void World::add_entity(unique_ptr<IEntity> entity) { _pimpl->add_entity(std::move(entity)); }
void World::add_system(unique_ptr<ISystem> system) { _pimpl->add_system(std::move(system)); }
void World::play() { _pimpl->play(); }
#pragma endregion

WorldImpl::WorldImpl(const string title, int width, int height)
{
	state = make_shared<GameState>();

	check([]{ return SDL_Init(SDL_INIT_EVERYTHING); });
	SDL_WM_SetCaption(title.c_str(), nullptr);
	check([]{ return SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1); });
	check([]{ return SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4); });
	check([]{ return SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); });
	surface = check<SDL_Surface*>([=]{ return SDL_SetVideoMode(width, height, 32, SDL_OPENGL | SDL_RESIZABLE); });

	add_system(make_unique<ControlSystem>(state));
	add_system(make_unique<MotionSystem>(state, width, height));
	add_system(make_unique<CollisionSystem>());
	add_system(make_unique<PhysicsSystem>());
	add_system(
		make_unique<RenderSystem>(
			make_unique<GLImmediateRenderer>(width, height)
		)
	);
	add_system(make_unique<UISystem>(state));
}

void WorldImpl::play()
{
	unsigned now, mspf = 1000 / maxFPS;
	state->last_frame = SDL_GetTicks();
	
	while (!state->shouldQuit)
	{
		frame();
        
        now = SDL_GetTicks();
        state->last_frame_time = now - state->last_frame;
        state->last_frame = now;
        

        if (state->last_frame_time < mspf)
            SDL_Delay(mspf - state->last_frame_time);
	}

	SDL_Quit();
}

void WorldImpl::add_entity(shared_ptr<IEntity> entity)
{
	entities.push_back(entity);

	for (auto& system : systems)
	{
		auto comps = system->required_components();
		if (comps.size() == 0) continue;

		auto matches = count_if(comps.begin(), comps.end(), [&](IComponent::ID requirement)
		{
			return entity->has_component(requirement);
		});

		if (matches == comps.size())
			system->add_entity(entity);
	}
}

void WorldImpl::add_system(unique_ptr<ISystem> system)
{
	systems.push_back(std::move(system));
}

void WorldImpl::frame()
{
	while (SDL_PollEvent(&event))
		for(auto& system : systems)
			if (system->event(event)) break;

	for(auto& system : systems)
		system->frame();
}