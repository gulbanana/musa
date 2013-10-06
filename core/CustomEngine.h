#pragma once
#include <core/IGameEngine.h>

class CustomEngine : public IGameEngine
{
private:
	std::unique_ptr<IGameEngine> _inner;
	std::vector<std::function<ISystem*()>> _factories;

public:
	CustomEngine(std::unique_ptr<IGameEngine> inner);

    void init(std::unique_ptr<GameSettings> settings, GameState* state) override;
	std::vector<std::unique_ptr<ISystem>> create_systems() override;

	void add_system(std::function<ISystem*()> systemFactory);
};

