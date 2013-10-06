#pragma once
#include <core/GLEngineBase.h>
#include <core/text/FontManager.h>

class TileEngine : public GLEngineBase
{
public:
	std::vector<std::unique_ptr<ISystem>> create_systems() override final;
};

