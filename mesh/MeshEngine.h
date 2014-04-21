#pragma once
#include <core/IGameEngine.h>
#include <core/GLEngineBase.h>

class MeshEngine : public GLEngineBase
{
private:
    std::set<std::unique_ptr<ISystem>> _ownedSystems;
    bool _wireframe;

public:
	MeshEngine(bool wireframe);
    void init(std::unique_ptr<GameSettings> settings, GameState* state) override;
	std::set<ISystem*> create_systems() override final;
};

