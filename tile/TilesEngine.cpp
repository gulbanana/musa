#include <tile/stdafx.h>
#include "TilesEngine.h"
using namespace std;

TilesEngine::TilesEngine()
{
}

TilesEngine::~TilesEngine()
{
}

vector<unique_ptr<ISystem>> TilesEngine::get_systems(GameSettings settings, shared_ptr<GameState> state)
{
	vector<unique_ptr<ISystem>> empty;
	return empty;
}