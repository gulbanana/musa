#pragma once
#include <core/IGameEngine.h>

class MeshEngine : public IGameEngine
{
private:
	bool _wireframe;

public:
	MeshEngine(bool wireframe);
	~MeshEngine();

	std::vector<std::unique_ptr<ISystem>> get_systems(GameSettings settings, std::shared_ptr<GameState> state) override;
};

