#pragma once
#include <core/framework.h>
#include <core/GameState.h>
#include <core/GameSettings.h>

class IGameEngine
{
public:
	virtual ~IGameEngine() {}
	virtual std::vector<std::unique_ptr<ISystem>> get_systems(GameSettings settings, std::shared_ptr<GameState> state) = 0;
};