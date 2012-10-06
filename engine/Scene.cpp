#include <vector>
#include <algorithm>
#include "Scene.h"
using namespace std;

#pragma region pimpl
class SceneImpl
{
	vector<unique_ptr<ISystem>> systems;
	vector<shared_ptr<IEntity>> entities;

public:
	SceneImpl();

	void add_entity(shared_ptr<IEntity> entity);
	void add_system(unique_ptr<ISystem>&& system);
	void frame();
};

Scene::Scene() : _pimpl(new SceneImpl()) {}
void Scene::add_entity(shared_ptr<IEntity> entity) { _pimpl->add_entity(entity); }
void Scene::add_system(unique_ptr<ISystem>&& system) { _pimpl->add_system(move(system)); }
void Scene::frame() { _pimpl->frame(); }
#pragma endregion

SceneImpl::SceneImpl() : entities(), systems()
{
}

void SceneImpl::add_entity(shared_ptr<IEntity> entity)
{
	entities.push_back(entity);

	for (auto& system : systems)
	{
		auto& comps = system->required_components();
		if (comps.size() == 0) continue;

		auto matches = count_if(comps.begin(), comps.end(), [&](IComponent::ID requirement)
		{
			return entity->has_component(requirement);
		});

		if (matches == comps.size())
			system->add_entity(entity);
	}
}

void SceneImpl::add_system(unique_ptr<ISystem>&& system)
{
	systems.push_back(move(system));

	//sort(begin(systems), end(systems));
}

void SceneImpl::frame()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
		for(auto& system : systems)
			if (system->on_event(event)) 
				break;

	for(auto& system : systems)
		system->on_frame();
}