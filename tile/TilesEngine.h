#pragma once
#include <core/IGameEngine.h>

class TilesEngine : public IGameEngine
{
private:

public:
	TilesEngine();
	~TilesEngine();

	std::vector<std::unique_ptr<ISystem>> get_systems(GameSettings settings, std::shared_ptr<GameState> state) override;
};

