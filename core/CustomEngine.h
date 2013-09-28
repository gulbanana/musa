#pragma once
#include <core/IGameEngine.h>

class CustomEngine : public IGameEngine
{
private:
	std::unique_ptr<IGameEngine> _inner;
	std::vector<std::unique_ptr<ISystem>> _extras;

public:
	CustomEngine(std::unique_ptr<IGameEngine> inner);
	~CustomEngine();

	std::vector<std::unique_ptr<ISystem>> get_systems(GameSettings settings, std::shared_ptr<GameState> state) override;
	void add_system(std::unique_ptr<ISystem> system);
};

