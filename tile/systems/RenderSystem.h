#pragma once
#include <core/framework.h>
#include "IBlitter.h"

class RenderSystem : public Identified<ISystem,SYS::Render,ThreadedSystemBase>
{
private:
	IBlitter* _blitter;

private:
	std::vector<ISystem::ID> required_systems() const override;
	void on_wake() override;

public:
	RenderSystem(IBlitter*);
	~RenderSystem();
};

