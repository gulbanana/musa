#pragma once
#include <core/framework.h>
#include "IGameEngine.h"

class GameImpl;

class Game
{
	GameImpl* _pimpl;

public:
	Game(GameSettings settings, std::unique_ptr<IGameEngine> engine);
	~Game();

	void play();
	void load_scene(std::vector<std::shared_ptr<IEntity>> level);
};