#pragma once
#include <core/IGameEngine.h>

class CustomEngine : public IGameEngine
{
private:
    GameState* _state;
	std::unique_ptr<IGameEngine> _inner;
    std::vector<std::function<ISystem*(GameState*)>> _factories;
    std::set<std::unique_ptr<ISystem>> _systems;

public:
	CustomEngine(std::unique_ptr<IGameEngine> inner);

    void init(std::unique_ptr<GameSettings> settings, GameState* state) override;
	std::set<ISystem*> create_systems() override;

    void add_system(std::function<ISystem*(GameState*)> systemFactory);
};

