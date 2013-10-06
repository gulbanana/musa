#include <core/stdafx.h>
#include "CustomEngine.h"
using namespace std;

CustomEngine::CustomEngine(unique_ptr<IGameEngine> inner) : _inner(move(inner)), _factories() {}

void CustomEngine::init(unique_ptr<GameSettings> settings, GameState* state)
{
    _inner->init(move(settings), state);
}

vector<unique_ptr<ISystem>> CustomEngine::create_systems()
{
	auto combinedSystems = _inner->create_systems();

	for (auto extraSystemBuilder : _factories)
	{
		combinedSystems.emplace_back(extraSystemBuilder());
	}
	
	return combinedSystems;
}

void CustomEngine::add_system(function<ISystem*()> systemFactory)
{
	_factories.push_back(systemFactory);
}