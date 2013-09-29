#include <tile/stdafx.h>
#include "TileEngine.h"
using namespace std;

TileEngine::TileEngine()
{
}

TileEngine::~TileEngine()
{
}

vector<unique_ptr<ISystem>> TileEngine::get_systems(GameSettings settings, shared_ptr<GameState> state)
{
	vector<unique_ptr<ISystem>> empty;
	return empty;
}