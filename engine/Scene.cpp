#include <vector>
#include <algorithm>
#include "Scene.h"
using namespace std;

Scene::Scene() : _nodes() {}

void Scene::add_entity(shared_ptr<IEntity> entity)
{
	_nodes.push_back(entity);
}

vector<weak_ptr<IEntity>> Scene::entities()
{
	vector<weak_ptr<IEntity>> weakRefs;

	for (auto& entity : _nodes)
		weakRefs.push_back(entity);

	return weakRefs;
}