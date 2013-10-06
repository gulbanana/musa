#pragma once
#include <core/framework.h>
#include <core/GameState.h>
#include <core/GameSettings.h>

class IGameEngine
{
public:
	virtual ~IGameEngine() {}
    virtual void init(std::unique_ptr<GameSettings> settings, GameState* state) = 0;
	virtual std::vector<std::unique_ptr<ISystem>> create_systems() = 0;
};