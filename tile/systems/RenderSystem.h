#pragma once
#include <core/framework.h>

class RenderSystem : public Identified<ISystem,SYS::Render,ThreadedSystemBase>
{
private:
	std::vector<ISystem::ID> required_systems() const override;
	void on_wake() override;

public:
	RenderSystem(void);
	~RenderSystem(void);
};

