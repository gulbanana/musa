#pragma once
#include <core/IGameEngine.h>
#include <core/GLEngineBase.h>

class MeshEngine : public GLEngineBase
{
private:
    bool _wireframe;

public:
	MeshEngine(bool wireframe);
	std::vector<std::unique_ptr<ISystem>> create_systems() override final;
};

