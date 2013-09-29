#pragma once
#include <core/IGameEngine.h>

class TileEngine : public IGameEngine
{
private:

public:
	TileEngine();
	~TileEngine();

	std::vector<std::unique_ptr<ISystem>> get_systems(GameSettings settings, std::shared_ptr<GameState> state) override;
};

