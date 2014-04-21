#pragma once
#include <core/GLEngineBase.h>
#include <core/text/FontManager.h>

class TileEngine : public GLEngineBase
{
    std::set<std::unique_ptr<ISystem>> _ownedSystems;

public:
    void init(std::unique_ptr<GameSettings> settings, GameState* state) override;
	std::set<ISystem*> create_systems() override final;
};

