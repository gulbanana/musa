#include <core/stdafx.h>
#include "CustomEngine.h"
using namespace std;

CustomEngine::CustomEngine(unique_ptr<IGameEngine> inner) : _inner(move(inner)), _extras() {}

CustomEngine::~CustomEngine() {}

vector<unique_ptr<ISystem>> CustomEngine::get_systems(GameSettings settings, shared_ptr<GameState> state)
{
	auto combinedSystems = _inner->get_systems(settings, state);

	for (auto& extraSystem : _extras)
	{
		combinedSystems.push_back(move(extraSystem));
	}
	
	return combinedSystems;
}

void CustomEngine::add_system(unique_ptr<ISystem> system)
{
	_extras.push_back(move(system));
}